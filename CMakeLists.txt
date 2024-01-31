cmake_minimum_required(VERSION 3.20)
project(Photomosaic)

set(CMAKE_CXX_STANDARD 17)

# setting compiler flag to NOT show deprecation warnings (triggered by stb library)
set(CMAKE_CXX_FLAGS "-Wno-deprecated")

## Do some research on how to copy the sampleImages folder
## into the build folder using cmake :)

# create a statically linked library named libimgLib
add_library(imgLib
        lib/include/Image.h
        lib/src/Image.cpp
        lib/include/Pixel.h
        lib/src/Pixel.cpp
        lib/src/photomosaic.cpp
        lib/include/photomosaic.h
        lib/include/kdTree.h
        lib/include/kdTree.h
)
target_include_directories(imgLib PRIVATE lib/include lib/stb)

# create the executable and use libimgLib created above
add_executable(${CMAKE_PROJECT_NAME} main.cpp
        lib/include/Image.h
        lib/src/Image.cpp
        lib/include/Pixel.h
        lib/src/Pixel.cpp
        lib/src/photomosaic.cpp
        lib/include/photomosaic.h
        lib/include/kdTree.h
        lib/include/kdTree.h
)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE lib/include)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE imgLib)