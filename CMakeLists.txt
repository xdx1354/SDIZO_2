cmake_minimum_required(VERSION 3.24)
project(Projekt2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projekt2 main.cpp MST/MST.cpp MST/MST.h structures/Tree.cpp structures/Tree.h structures/Queue.cpp structures/Queue.h shortest-path/ShortestPath.cpp shortest-path/ShortestPath.h)
