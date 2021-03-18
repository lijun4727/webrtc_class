#include "ffmpeg_base.h"
#include "save_image.h"
#include "srs_librtmp.h"
//#include "FFmpegPushH264.h"

#include <string.h>
#include <stdlib.h>

srs_rtmp_t rtmp = 0;

int32_t save_image(const char *filename, uint8_t *rgb_buf, int32_t width, int32_t height)
{
    return save_image_jpg(filename, rgb_buf, width, height) == true ? 1 : 0;
}

int32_t connect_rtmp(const char *rtmp_url)
{
    if (rtmp != 0)
    {
        srs_rtmp_destroy(rtmp);
    }
    rtmp = srs_rtmp_create(rtmp_url);
    if (!rtmp)
    {
        return -1;
    }
    if (srs_rtmp_handshake(rtmp) != 0)
    {
        return -2;
    }
    if (srs_rtmp_connect_app(rtmp) != 0)
    {
        return -3;
    }
    if (srs_rtmp_publish_stream(rtmp) != 0)
    {
        return -4;
    }

    //000000016742802995A014016E400000000168CE3880
    uint8_t sps_pps_data[] = {0x00, 0x00, 0x00, 0x01, 0x67, 0x42, 0x80, 0x29, 0x95, 0xA0, 0x14, 0x01, 0x6E, 0x40,
                              0x00, 0x00, 0x00, 0x01, 0x68, 0xCE, 0x38, 0x80};
    return srs_h264_write_raw_frames(rtmp, sps_pps_data, sizeof(sps_pps_data), 0, 0);
}

void destroy_rtmp()
{
    srs_rtmp_destroy(rtmp);
    rtmp = 0;
}

int read_h264_frame(char *data, int size, char **pp, int *pnb_start_code, int fps,
                    char **frame, int *frame_size, int *dts, int *pts)
{
    char *p = *pp;

    // @remark, for this demo, to publish h264 raw file to SRS,
    // we search the h264 frame from the buffer which cached the h264 data.
    // please get h264 raw data from device, it always a encoded frame.
    if (!srs_h264_startswith_annexb(p, size - (p - data), pnb_start_code))
    {
        //srs_human_trace("h264 raw data invalid.");
        return -1;
    }

    // @see srs_write_h264_raw_frames
    // each frame prefixed h.264 annexb header, by N[00] 00 00 01, where N>=0,
    // for instance, frame = header(00 00 00 01) + payload(67 42 80 29 95 A0 14 01 6E 40)
    *frame = p;
    p += *pnb_start_code;

    for (; p < data + size; p++)
    {
        if (srs_h264_startswith_annexb(p, size - (p - data), NULL))
        {
            break;
        }
    }

    *pp = p;
    *frame_size = p - *frame;
    if (*frame_size <= 0)
    {
        //srs_human_trace("h264 raw data invalid.");
        return -1;
    }

    // @remark, please get the dts and pts from device,
    // we assume there is no B frame, and the fps can guess the fps and dts,
    // while the dts and pts must read from encode lib or device.
    *dts += 1000 / fps;
    *pts = *dts;

    return 0;
}

int32_t push_h264_to_rtmp(uint8_t *data, int32_t size, frame_type ft, int32_t fps)
{
    static uint32_t pts = 0;
    static uint32_t dts = 0;
    dts += 1000 / fps;
    pts = dts;

    uint8_t* data_with_start_code;
    int start_code_size;
    switch (ft)
    {
    case frame_type_i:
    {
        //0000000165B8041014C038008B0D0D3A071
        uint8_t start_code[] = {0x00, 0x00,0x00,0x01,0x65,0xB8,0x04,0x10,0x14,0xC0,0x38,0x00,0x8B,0x0D,0x0D,0x3A,0x07,0x10};
        start_code_size = sizeof(start_code);
        data_with_start_code = malloc(size + start_code_size);
        memcpy(data_with_start_code, start_code, start_code_size);
        memcpy(data_with_start_code + start_code_size, data, size);
    }
    break;
    case frame_type_p:
    {
        //0000000141E02041F8CDDC562BBDEFAD2F
        uint8_t start_code[] = {0x00, 0x00, 0x00, 0x01, 0x41, 0xE0, 0x20, 0x41, 0xF8, 0xCD, 0xDC, 0x56, 0x2B, 0xBD, 0xEF, 0xAD, 0x2F};
        start_code_size = sizeof(start_code);
        data_with_start_code = malloc(size + start_code_size);
        memcpy(data_with_start_code, start_code, start_code_size);
        memcpy(data_with_start_code + start_code_size, data, size);
    }
    break;
    default:
        return -2;
    }

    int ret = srs_h264_write_raw_frames(rtmp, (char *)data_with_start_code, size + start_code_size, dts, pts);
    free(data_with_start_code);
    return ret;

    // // @remark, to decode the file.
    // char *p = data;
    // int count = 0;
    // char *data_with_annexb = NULL;
    // int size_with_annexb = 0;
    // int nb_start_code = 0;
    // if (read_h264_frame(data, (int)size, &p, &nb_start_code, fps, &data_with_annexb, &size_with_annexb, &dts, &pts) < 0)
    // {
    //     //srs_human_trace("read a frame from file buffer failed.");
    //     return -1;
    // }

    // int ret = srs_h264_write_raw_frames(rtmp, data_with_annexb, size_with_annexb, dts, pts);
    // return ret;
}

// int32_t rtmp_init(uint8_t* h264buffer, int32_t iPsLength)
// {
//     if (isIdrFrame1((uint8_t *)h264buffer, iPsLength))
//     {
//         int spspps_len = GetSpsPpsFromH264((uint8_t *)h264buffer, iPsLength);
//         if (spspps_len > 0)
//         {
//             char *spsbuffer = (char *)malloc(spspps_len);
//             memcpy(spsbuffer, h264buffer, spspps_len);
//             RtmpInit(spsbuffer, spspps_len);
//             free(spsbuffer);
//             return 0;
//         }
//     }
//     return -1;
// }

// void rtmp_uninit()
// {
//     RtmpUnit();
// }

// int32_t rtmp_push_h264(uint8_t* data, int32_t size)
// {
//     return VideoWrite(data, size);
// }