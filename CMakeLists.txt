cmake_minimum_required(VERSION 3.20)

project(OpenCVProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(OpenCV_DIR "/usr/lib/cmake/opencv5")

find_package(OpenCV REQUIRED COMPONENTS
        core
        imgproc
        imgcodecs
        highgui
        videoio
        objdetect
        dnn
)

add_executable(OpenCVProject main.cpp
        Camera.h
        Preprocessor.h
        Application.h
        FaceDetector.h)

target_include_directories(OpenCVProject PRIVATE
        ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(OpenCVProject PRIVATE
        ${OpenCV_LIBS}
)