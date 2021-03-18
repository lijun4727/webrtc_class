#pragma once

#include <stdint.h>

/*
如果是虚拟机需要配置--enable-libx264 --enable-gpl
./configure --enable-nonfree --enable-pic --enable-shared --disable-x86asm --enable-libx264 --enable-gpl
*/

int32_t FFmpeg_H264EncoderInit();

void FFmpeg_H264EncoderRelease();

int32_t FFmpeg_H264Encode(uint8_t* ybuf, uint8_t* ubuf, uint8_t* vbuf, int32_t width, int32_t height, unsigned char** outBuf, int32_t* outBufSize, int32_t fps, int32_t bit_rate);