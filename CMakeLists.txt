cmake_minimum_required(VERSION 3.22)

project(myNode)

# 设置编译选项
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_definitions(-DV8_COMPRESS_POINTERS)

# 添加库路径
if(APPLE)
    set(V8_LIB_PATH "lib/mac/v8")
    set(LIBEV_LIB_PATH "lib/mac/libev")
elseif(UNIX)
    set(V8_LIB_PATH "lib/linux/v8")
    set(LIBEV_LIB_PATH "lib/linux/libev")
endif()

set(INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)

link_directories(${V8_LIB_PATH})
link_directories(${LIBEV_LIB_PATH})

include_directories(
    ${INCLUDE_PATH}/v8
    ${INCLUDE_PATH}/libev
    ${INCLUDE_PATH}/common
)

file(GLOB SOURCES "src/core/*.cc" "src/utils/*.cc" "myNode.cc")

add_executable(Node ${SOURCES})

target_link_libraries(
    Node
    PRIVATE
    ev
    v8_monolith
    v8_libbase
    v8_libplatform
    dl
    pthread
)
