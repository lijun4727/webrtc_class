#pragma once

#include <libavcodec/avcodec.h>
#include <stdint.h>

#include "types.h"

/**
 视频流解码器初始化
 @param ctx 解码参数结构体AVCodecParameters
 @see FFmpeg_H264DecoderInit，此为解码H264视频流
 @return 初始化成功返回0，否则<0
 */
int32_t FFmpeg_VideoDecoderInit(AVCodecParameters* ctx);

/**
 H264视频流解码器初始化
 @return 初始化成功返回0，否则<0
 */
int32_t FFmpeg_H264DecoderInit(void);

/**
 释放解码器
 @return 初始化成功返回0，否则<0
 */
void FFmpeg_VideoDecoderRelease(void);

//return 0:暂未收到解码数据，-1：解码失败，1：解码成功

/**
 解码视频流数据
 @param inbuf 视频裸流数据
 @param inbufSize 视频裸流数据大小
 @param framePara 接收帧参数数组：{width,height,linesize1,linesiz2,linesize3}
 @param outRGBBuf 输出RGB数据(若已申请内存)
 @return 成功返回解码数据帧大小，否则<=0
 */
int32_t FFmpeg_H264Decode(unsigned char* inbuf, int32_t inbufSize, int32_t* framePara, unsigned char* outRGBBuf, 
    unsigned char** outYBuf, unsigned char** outUBuf, unsigned char** outVBuf, int32_t need_key_frame, frame_type* pt);