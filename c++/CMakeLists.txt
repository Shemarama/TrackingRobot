cmake_minimum_required(VERSION 2.8)
project( Robot )
find_package( OpenCV REQUIRED )
add_executable( Robot main.cpp )
target_link_libraries( Robot ${OpenCV_LIBS} )