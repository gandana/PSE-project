cmake_minimum_required(VERSION 3.20)
project(MeetingPlanner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(CORE_SOURCES
        src/tinyxml.cpp
        src/tinyxmlerror.cpp
        src/tinyxmlparser.cpp
        src/tinystr.cpp
        src/SystemParser.cpp
        src/SystemOutput.cpp
)

add_executable(MeetingPlanner src/main.cpp ${CORE_SOURCES})


include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(run_meeting_tests tests/DomainTests.cpp tests/ParserTests.cpp)

target_link_libraries(run_meeting_tests gtest_main)
target_sources(run_meeting_tests PRIVATE ${CORE_SOURCES})
target_include_directories(run_meeting_tests PRIVATE include)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input DESTINATION ${CMAKE_CURRENT_BINARY_DIR})