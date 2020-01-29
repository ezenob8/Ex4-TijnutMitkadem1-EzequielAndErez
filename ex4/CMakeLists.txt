cmake_minimum_required(VERSION 3.15)
project(ex4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(ex4 main.cpp IServer.h SerialServer.cpp SerialServer.h IClientHandler.h MyClientHandler.cpp MyClientHandler.h ISolver.h ICacheManager.h FileCacheManager.h OA.h ISearcher.h ISearchable.h BFS.h Matrix.cpp Matrix.h State.h DFS.h Cell.h ParallelServer.cpp ParallelServer.h BestFS.h Astar.h PriorityQueue.h)