cmake_minimum_required(VERSION 3.22)

project(myNode)

# 设置编译选项
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add_compile_definitions(-DV8_COMPRESS_POINTERS)
add_definitions(-DV8_COMPRESS_POINTERS)

# 添加库路径
set(V8_LIB_PATH "lib/v8")
set(LIBEV_LIB_PATH "lib/libev")
set(Boost_LIBRARY_DIRS "lib/boost")

link_directories(${V8_LIB_PATH})
link_directories(${LIBEV_LIB_PATH})
link_directories(${Boost_LIBRARY_DIRS})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/v8
    ${CMAKE_CURRENT_SOURCE_DIR}/include/libev
    ${CMAKE_CURRENT_SOURCE_DIR}/include/common
    ${CMAKE_CURRENT_SOURCE_DIR}/include/bost
)

# set(Boost_USE_STATIC_LIBS ON)
# set(Boost_USE_MULTITHREADED ON)
# find_package(Boost REQUIRED COMPONENTS thread)
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
    boost_thread
)
