cmake_minimum_required(VERSION 2.8)
project( Robot )
find_package( OpenCV REQUIRED )

include_directories(include)

set(serial_SRCS src/serial.cc include/serial/serial.h include/serial/v8stdint.h)
if(UNIX)
    list(APPEND serial_SRCS src/impl/unix.cc)
    list(APPEND serial_SRCS src/impl/list_ports/list_ports_linux.cc)
else()
    list(APPEND serial_SRCS src/impl/win.cc)
    list(APPEND serial_SRCS src/impl/list_ports/list_ports_win.cc)
endif()

## Add serial library
add_library(serial ${serial_SRCS})
if(UNIX AND NOT APPLE)
    target_link_libraries(serial rt)
endif()

## Build your executable
add_executable( Robot objectDetection2.cpp )
## Link your executable against the library
target_link_libraries(Robot serial ${OpenCV_LIBS} )
