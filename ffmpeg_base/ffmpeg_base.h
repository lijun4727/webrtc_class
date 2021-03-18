#ifndef FFMPEG_BASE_H_
#define FFMPEG_BASE_H_

#include <stdint.h>
#include "types.h"

int32_t save_image(const char* filename, uint8_t* rgb_buf, int32_t width, int32_t height);

int32_t connect_rtmp(const char* rtmp_url);

void destroy_rtmp();

int32_t push_h264_to_rtmp(uint8_t *data, int32_t size, frame_type ft, int32_t fps);

// int32_t rtmp_init(uint8_t* data, int32_t size);

// void rtmp_uninit();

// int32_t rtmp_push_h264(uint8_t* data, int32_t size);

#endif