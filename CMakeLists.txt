cmake_minimum_required(VERSION 3.10)

project(myNode)

# 设置编译选项
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_definitions(-DV8_COMPRESS_POINTERS)

# 添加V8库路径
set(V8_LIB_PATH "lib")
link_directories(${V8_LIB_PATH})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/utils)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/v8)

file(GLOB SOURCES "src/core/*.cc" "src/utils/*.cc" "myNode.cc")

add_executable(Node ${SOURCES})

target_link_libraries(Node PRIVATE v8_monolith v8_libbase v8_libplatform dl pthread)