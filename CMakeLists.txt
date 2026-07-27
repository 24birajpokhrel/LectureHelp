cmake_minimum_required(VERSION 3.14)
project(LectureHelp LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GGML_CUDA OFF CACHE BOOL "" FORCE)

add_subdirectory(extern/whisper.cpp)
add_subdirectory(extern/llama.cpp)
add_subdirectory(src)
