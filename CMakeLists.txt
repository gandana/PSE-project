cmake_minimum_required(VERSION 3.20)
project(MeetingPlanner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# 1. Alleen de gedeelde logica (GEEN main en GEEN testen)
set(CORE_SOURCES
        src/tinyxml.cpp
        src/tinyxmlerror.cpp
        src/tinyxmlparser.cpp
        src/tinystr.cpp
        src/SystemParser.cpp
        src/SystemOutput.cpp
        # Room.cpp en Meeting.cpp moeten hier ook bij als je die hebt!
)

# 2. Het echte programma: main + core
add_executable(MeetingPlanner src/main.cpp ${CORE_SOURCES}
        src/Room.cpp
        src/Meeting.cpp
        src/MeetingPlanner.cpp)

# --- Google Test setup ---
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 3. De Test Executable
# Hier voeg je alle test-bestanden toe (ook RoomTesting.cpp)
add_executable(run_meeting_tests
        tests/RoomTesting.cpp
        tests/DomainTests.cpp
        tests/ParserTests.cpp
        ${CORE_SOURCES}
)

target_link_libraries(run_meeting_tests GTest::gtest_main)
target_include_directories(run_meeting_tests PRIVATE include)

# Bestanden kopiëren voor de tests
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input DESTINATION ${CMAKE_CURRENT_BINARY_DIR})