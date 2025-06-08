cmake_minimum_required(VERSION 3.31)
project(Assignment)

set(CMAKE_CXX_STANDARD 20)

add_executable(Assignment src/main.cpp
        src/entities/Transaction.h
        src/utilities/TransactionReader.cpp
        src/utilities/TransactionReader.h
        src/utilities/channelSeperator.cpp
        src/utilities/channelSeperator.h)
