extern "C"
{
#include "FFmpegVideoDecoder.h"
#include "FFmpegVideoEncoder.h"
#include "ffmpeg_base.h"
}

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

int main()
{
	int ret = FFmpeg_H264DecoderInit();
	if (ret != 0)
		return 0;
	ret = FFmpeg_H264EncoderInit();
	if (ret != 0)
		return 0;

	ifstream ifs;
	ifs.open("video_stream.mkv",ios::in | ios::binary);
	if( !ifs.is_open() )
	{
		cout << "文件打开失败" << endl;
		return 0;
	}
	ifs.seekg(0, std::ios::end);
	size_t size = ifs.tellg();
	ifs.seekg(0, std::ios::beg);
	char *buf = (char *)malloc(size);
	ifs.read(buf, size);
	ifs.close();

	int frameInfo[5];
	ret = FFmpeg_H264Decode((uint8_t *)buf, size, frameInfo, nullptr, nullptr, nullptr, nullptr, 1, nullptr);
	if(ret != 0){
		cout << "解码失败" << endl;
		return 0;
	}

	const char* rtmpUrl = "rtmp://192.168.1.5:1935/live/L17LTlsVqMNTZyLKMIFSD2x28MlgPJ0SDZVHnHJPxMKi0tWx";
	ret = connect_rtmp(rtmpUrl);

	uint8_t* outYBuf;
	uint8_t* outUBuf;
	uint8_t* outVBuf;	
	ret = FFmpeg_H264Decode((uint8_t *)buf, size, nullptr, nullptr, &outYBuf, &outUBuf, &outVBuf, 0, nullptr);
	if(ret >= 0){
		unsigned char* outBuf;
		int32_t outBufSize;
		int fps = 60;
		ret = FFmpeg_H264Encode(outYBuf, outUBuf, outVBuf, frameInfo[0], frameInfo[1], &outBuf, &outBufSize, fps, 4000000);
		if(ret == 0){
			
			ret = push_h264_to_rtmp(outBuf, outBufSize, frame_type_i, fps);

			uint8_t *rgbBuf = (uint8_t *)malloc(frameInfo[0] * frameInfo[1] * 3);
			ret = FFmpeg_H264Decode(outBuf, outBufSize, NULL, rgbBuf, NULL, NULL, NULL, 1, nullptr);
			if(ret == 0){
				save_image("./test1333333333333333333.jpg", rgbBuf, frameInfo[0], frameInfo[1]);
			}
			free(rgbBuf);
		}
	}	
	
	free(buf);
	FFmpeg_VideoDecoderRelease();
	FFmpeg_H264EncoderRelease();
	return 0;
}