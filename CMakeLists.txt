cmake_minimum_required(VERSION 3.31)
project(Assignment)

set(CMAKE_CXX_STANDARD 20)

add_executable(Assignment src/main.cpp
        src/entities/Transaction.cpp
        src/entities/Transaction.h
        src/utilities/TransactionReader.cpp
        src/utilities/TransactionReader.h
        src/utilities/PerformanceTracker.cpp
        src/utilities/PerformanceTracker.h
        src/utilities/ChannelSeparator.cpp
        src/utilities/ChannelSeparator.h
        src/utilities/Sorter.cpp
        src/utilities/Sorter.h
        src/utilities/Searcher.cpp
        src/utilities/Searcher.h
        src/utilities/JsonExport.cpp
        src/utilities/JsonExport.h
)
