cmake_minimum_required(VERSION 3.29)
project(lab0)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab0 lab0.cpp
        FileManager.h
        FileManager.cpp
        TextProcessor.h
        TextProcessor.cpp
        WordCounter.h
        WordCounter.cpp
)
