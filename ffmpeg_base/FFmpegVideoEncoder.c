#include "FFmpegVideoEncoder.h"

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>

AVPacket *pkt;
AVCodecContext *c = NULL;
AVFrame *frame;
AVCodec *codec;

int32_t FFmpeg_H264EncoderInit()
{
	//avcodec_register_all();
	codec = avcodec_find_encoder(AV_CODEC_ID_H264);
	if (!codec)
		return -1;

	c = avcodec_alloc_context3(codec);
	if (!c)
		return -2;

	frame = av_frame_alloc();
	if (!frame)
		return -3;

	pkt = av_packet_alloc();
	if (!pkt)
		return -4;

	return 0;
}

int32_t FFmpeg_H264Encode(uint8_t *ybuf, uint8_t *ubuf, uint8_t *vbuf, int32_t width, int32_t height, unsigned char **outBuf, int32_t *outBufSize, int32_t fps, int32_t bit_rate)
{
	/* put sample parameters */
	c->bit_rate = bit_rate;
	/* resolution must be a multiple of two */
	c->width = width;
	c->height = height;
	/* frames per second */
	c->time_base = (AVRational){1, fps};
	c->framerate = (AVRational){fps, 1};
	c->codec_id = codec->id;
	c->codec_type = AVMEDIA_TYPE_VIDEO;
	/* emit one intra frame every ten frames
	 * check frame pict_type before passing frame
	 * to encoder, if frame->pict_type is AV_PICTURE_TYPE_I
	 * then gop_size is ignored and the output of encoder
	 * will always be I frame irrespective to gop_size
	 */
	// c->qmin = 10;
	// c->qmax = 51;
	// c->gop_size = 0;
	// c->max_b_frames = 0;
	c->pix_fmt = AV_PIX_FMT_YUV420P;

	AVDictionary *param = NULL;
	int ret = 0;
	if (c->codec_id == AV_CODEC_ID_H264)
	{
		av_dict_set(&param, "preset", "slow", 0);
		av_dict_set(&param, "tune", "zerolatency", 0);
	}

	ret = avcodec_open2(c, codec, &param);
	if (ret < 0)
	{
		fprintf(stderr, "Could not open codec: %s\n", av_err2str(ret));
		return -1;
	}

	frame->format = c->pix_fmt;
	frame->width = c->width;
	frame->height = c->height;

	ret = av_frame_get_buffer(frame, 32);
	if (ret < 0)
	{
		fprintf(stderr, "Could not allocate the video frame data\n");
		return -2;
	}
	ret = av_frame_make_writable(frame);
	if (ret != 0)
		return -3;

	frame->data[0] = ybuf;
	frame->data[1] = ubuf;
	frame->data[2] = vbuf;
	ret = avcodec_send_frame(c, frame);
	if (ret < 0)
	{
		fprintf(stderr, "Error sending a frame for encoding\n");
		return -4;
	}

	ret = avcodec_receive_packet(c, pkt);
	if (ret != 0 && ret != AVERROR_EOF)
	{
		return -5;
	}

	if (ret == 0)
	{
		*outBuf = pkt->data;
		*outBufSize = pkt->size;
		av_packet_unref(pkt);
	}

	return 0;
}

void FFmpeg_H264EncoderRelease()
{
	if (c)
	{
		avcodec_free_context(&c);
		c = NULL;
	}

	if (frame)
	{
		av_frame_unref(frame);
		av_frame_free(&frame);
		frame = NULL;
	}

	if (pkt)
	{
		av_packet_unref(pkt);
		av_packet_free(&pkt);
		pkt = NULL;
	}
}