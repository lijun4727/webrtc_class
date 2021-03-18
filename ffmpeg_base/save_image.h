#ifndef SAVE_IMAGE_H_
#define SAVE_IMAGE_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

int save_image_jpg(const char* filename, uint8_t* rgb_buf, int32_t width, int32_t height);

#ifdef __cplusplus
}
#endif

#endif