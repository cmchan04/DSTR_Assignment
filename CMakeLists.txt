cmake_minimum_required(VERSION 3.31)
project(Assignment)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.12.0
)

FetchContent_MakeAvailable(json)

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
        src/entities/DoublyLinkedList.cpp
        src/entities/DoublyLinkedList.h
        src/utilities/StringUtil.cpp
        src/utilities/StringUtil.h
)

target_link_libraries(Assignment PRIVATE nlohmann_json::nlohmann_json)
