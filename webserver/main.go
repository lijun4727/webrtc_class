package main

import (
	"WebRTCDemo/config"
	"WebRTCDemo/webserver/route"
)

// func ffmpeg_thread() {
// 	ret := C.FFmpeg_H264DecoderInit()
// 	if ret != 0 {
// 		fmt.Println("ffmpeg init failed")
// 		return
// 	}

// 	fp, err := os.Open("video_stream.mkv")
// 	if err != nil {
// 		fmt.Println(err)
// 	}

// 	info, _ := fp.Stat()
// 	buf := make([]uint8, info.Size())
// 	size := (int32)(info.Size())

// 	for {
// 		lens, err := fp.Read(buf)
// 		if err == io.EOF || lens < 0 {
// 			break
// 		}
// 	}
// 	fp.Close()
// 	fmt.Print(string(buf))

// 	var videoInfo [5]int32
// 	var rgbBuf [640 * 480 * 3]uint8
// 	ret = C.FFmpeg_H264Decode((*C.uchar)((unsafe.Pointer(&buf[0]))), C.int32_t(size), (*C.int32_t)(unsafe.Pointer(&videoInfo[0])), (*C.uchar)(unsafe.Pointer(&rgbBuf[0])), nil, nil, nil)
// 	if ret >= 0 {
// 		C.save_image(C.CString("test.jpg"), (*C.uchar)(unsafe.Pointer(&rgbBuf[0])), C.int(640), C.int(480))
// 	}
// }

func main() {
	// {
	// 	ret := C.FFmpeg_H264DecoderInit()
	// 	if ret != 0 {
	// 		fmt.Println("ffmpeg init failed")
	// 		return
	// 	}

	// 	fp, err := os.Open("video_stream.mkv")
	// 	if err != nil {
	// 		fmt.Println(err)
	// 	}

	// 	info, _ := fp.Stat()
	// 	buf := make([]uint8, info.Size())
	// 	size := (int32)(info.Size())

	// 	for {
	// 		lens, err := fp.Read(buf)
	// 		if err == io.EOF || lens < 0 {
	// 			break
	// 		}
	// 	}
	// 	fp.Close()
	// 	fmt.Print(string(buf))

	// 	ret = C.push_h264_to_rtmp((*C.uchar)(unsafe.Pointer(&buf[0])), (C.int32_t)((size)))

	// 	var videoInfo [5]int32
	// 	var rgbBuf [640 * 480 * 3]uint8
	// 	ret = C.FFmpeg_H264Decode((*C.uchar)((unsafe.Pointer(&buf[0]))), C.int32_t(size), (*C.int32_t)(unsafe.Pointer(&videoInfo[0])), (*C.uchar)(unsafe.Pointer(&rgbBuf[0])), nil, nil, nil, C.int32_t(1))
	// 	if ret >= 0 {
	// 		C.save_image(C.CString("test.jpg"), (*C.uchar)(unsafe.Pointer(&rgbBuf[0])), C.int(640), C.int(480))
	// 	}
	// }

	// err := handler.MediaHandle.Init()
	// if err != nil {
	// 	fmt.Println("MediaHandle init error")cccc
	// 	return
	// }
	// handler.MediaHandle.Start(1)

	router := route.Router()
	router.RunTLS(config.WebServerHostTLS, "ssl/server.crt", "ssl/server.key")
	//C.FFmpeg_VideoDecoderRelease()
}
