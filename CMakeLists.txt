cmake_minimum_required(VERSION 3.24)
project(Projekt2)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(Projekt2 main.cpp MST/MST.cpp MST/MST.h  structures/Queue.cpp structures/Queue.h shortest-path/ShortestPath.cpp shortest-path/ShortestPath.h util/Time.cpp util/Time.h)
