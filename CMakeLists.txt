PROJECT(streamer)
cmake_minimum_required(VERSION 3.13)


include_directories(/usr/local/include /usr/include)
link_directories(/usr/local/lib /usr/lib)

SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD OFF)

find_package(Boost COMPONENTS thread system REQUIRED)


INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

  
add_executable(streamer
 	src/LEDStreamer.cpp
 	src/UDPClient.h
 	src/UDPClient.cpp
)

target_link_libraries(streamer ${Boost_LIBRARIES})
