package handler

import (
	"net/http"

	"github.com/gin-gonic/gin"
)

// /*
// #cgo CFLAGS: -I../../ffmpeg_base/include
// #cgo LDFLAGS: -L../../ffmpeg_base/lib -lffmpeg_base
// #cgo LDFLAGS: -Wl,-rpath="../../ffmpeg_base/lib"
// #include "../../ffmpeg_base/FFmpegVideoDecoder.h"
// #include "../../ffmpeg_base/ffmpeg_base.h"
// */
// import "C"

//var MediaHandle media_handle.MediaHandle

// type MediaData struct {
// 	VideoCodecs string `json:"videoCodecs,omitempty"`
// 	Data        string `json:"data,omitempty"`
// }

//DefaultHomePageHandler: 处理默认首页
func DefaultHomePageHandler(c *gin.Context) {
	c.Redirect(http.StatusFound, "/static/index.html")
}

// func Update(c *gin.Context) {
// 	// formVideoCodecs := c.PostForm("codecs")
// 	formKind := c.PostForm("kind")
// 	// formSize := c.PostForm("size")
// 	// fmt.Println("videoCodecs=" + formVideoCodecs + ",kind=" + formKind + ",size=" + formSize)
// 	stream, err := c.FormFile("data")
// 	if err == nil && formKind == "video" {
// 		//err = c.SaveUploadedFile(stream, "video_stream.mkv")

// 		// if err == nil {
// 		// 	fp, err := os.Open("video_stream.mkv")
// 		// 	if err != nil {
// 		// 		fmt.Println(err)
// 		// 	}

// 		// 	info, _ := fp.Stat()
// 		// 	buf := make([]uint8, info.Size())
// 		// 	//size := (int32)(info.Size())
// 		// 	l := len(buf)
// 		// 	fmt.Print(l)
// 		// 	for {
// 		// 		lens, err := fp.Read(buf)
// 		// 		if err == io.EOF || lens < 0 {
// 		// 			break
// 		// 		}
// 		// 	}
// 		// 	fp.Close()

// 		// 	l = len(buf)
// 		// 	fmt.Print(l)
// 		// 	MediaHandle.AddData(buf)
// 		// }

// 		size := stream.Size
// 		if size > 0 {
// 			file, err := stream.Open()
// 			if err == nil {
// 				data, err := ioutil.ReadAll(file)
// 				if err == nil {
// 					if int64(len(data)) == size {
// 						MediaHandle.AddData(data)
// 					}
// 				}
// 			}
// 		}
// 	}

// 	//fmt.Println("media arrive")
// 	c.JSON(http.StatusOK, gin.H{
// 		"code": "OK",
// 	})
// }

// func TLSHandler() gin.HandlerFunc {
// 	return func(c *gin.Context) {
// 		secureMiddleware := secure.New(secure.Options{
// 			SSLRedirect: true,
// 			SSLHost:     "0.0.0.0:8081",
// 		})
// 		err := secureMiddleware.Process(c.Writer, c.Request)

// 		if err != nil {
// 			return
// 		}
// 		c.Next()
// 	}
// }
