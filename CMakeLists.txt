cmake_minimum_required(VERSION 3.10)
project (font-rendering)

set(THIRD_PARTY_DIR $ENV{THIRD_PARTY} CACHE PATH "Third party directory")
set(CUR_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CUR_SRC_DIR}/source/)

add_subdirectory(${CUR_SRC_DIR}/source/)

