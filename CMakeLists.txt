cmake_minimum_required(VERSION 2.8.12)
project(MD5Encrypter)

add_definitions("-std=c++17")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
find_package( ZLIB REQUIRED )

add_executable(md5 md5.cpp)
target_link_libraries(md5 ${CONAN_LIBS})
