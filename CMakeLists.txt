cmake_minimum_required(VERSION 3.2)
project(7__Markov_Bot)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(7__Markov_Bot ${SOURCE_FILES} fileManager.h fileManager.cpp dictionaryManager.h dictionaryManager.cpp dictionary.h dictionary.h markov.h markov.cpp arguments.h arguments.cpp)