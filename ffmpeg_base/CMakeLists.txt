#Debug建立cmake -DCMAKE_BUILD_TYPE=Debug ..

# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.0)

# 项目信息
project (ffmpeg_base)

#include_directories("../common")

# 查找当前目录下的所有源文件
aux_source_directory(. SELF_SRCS)
#aux_source_directory(../common COMMON_SRCS)

# 指定生成目标
#add_executable(media_server ${SELF_SRCS} ${COMMON_SRCS})

# 根据库文件代码生成库SHARED STATIC
add_library(ffmpeg_base SHARED ${SELF_SRCS})

# 创建动态库别名
##add_library(decode ALIAS ffmpeg_base)

#target_include_directories(ffmpeg_base PUBLIC  ${PROJECT_SOURCE_DIR})

target_link_libraries(ffmpeg_base avformat avcodec avutil swscale)

# execute_process(COMMAND mkdir ../lib 
#                 COMMAND mkdir ../include
#                 COMMAND cp libffmpeg_base.so ../lib
#                 COMMAND cp ../fun.h ../include)

ADD_CUSTOM_COMMAND(
                TARGET ffmpeg_base
                COMMAND rm -rf ${PROJECT_SOURCE_DIR}/lib
                COMMAND rm -rf ${PROJECT_SOURCE_DIR}/include
                COMMAND mkdir ${PROJECT_SOURCE_DIR}/lib 
                COMMAND mkdir ${PROJECT_SOURCE_DIR}/include
                COMMAND cp libffmpeg_base.* ${PROJECT_SOURCE_DIR}/lib
                COMMAND cp ${PROJECT_SOURCE_DIR}/*.h ${PROJECT_SOURCE_DIR}/include)