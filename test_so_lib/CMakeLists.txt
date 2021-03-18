#Debug建立cmake -DCMAKE_BUILD_TYPE=Debug ..

# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.0)

# 项目信息
project (test_so_lib)

include_directories("../ffmpeg_base/include")

# 查找当前目录下的所有源文件
aux_source_directory(. SELF_SRCS)
#aux_source_directory(../common COMMON_SRCS)


# 指定生成目标
add_executable(test_so_lib ${SELF_SRCS})

#target_link_libraries(media_server pthread boost_thread)

message("test_4_BINARY_DIR = ${PROJECT_SOURCE_DIR}")

target_link_libraries (test_so_lib ${PROJECT_SOURCE_DIR}/../ffmpeg_base/lib/libffmpeg_base.so)