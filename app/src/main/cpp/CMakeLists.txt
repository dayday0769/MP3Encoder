# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.6)

#设置变量SRC_DIR为lamemp3的所在路径
set(SRC_DIR lame)

#指定头文件所在，可以多次调用，指定多个路径
include_directories(lame/include)

#添加自自定义的so库时，有两种方式，一种添加一个目录，一种一个个文件添加

#设定一个目录
aux_source_directory(lame SRC_LIST)

#将前面目录下所有的文件都添加进去
add_library(mp3encoder SHARED mp3encoder.cpp ${SRC_LIST})

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
# 指定依赖库的名称
target_link_libraries( # Specifies the target library.
        mp3encoder

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})