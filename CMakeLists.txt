cmake_minimum_required(VERSION 3.20)
project(MeetingPlanner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# 1. ALLE logica bestanden (De "motor" van je programma)
# Hier moeten alle .cpp bestanden staan behalve main.cpp en de tests.
set(CORE_SOURCES
        src/tinyxml.cpp
        src/tinyxmlerror.cpp
        src/tinyxmlparser.cpp
        src/tinystr.cpp
        src/SystemParser.cpp
        src/SystemOutput.cpp
        src/Room.cpp
        src/Meeting.cpp
        src/MeetingPlanner.cpp
        src/Campus.cpp
        src/Building.cpp
        src/Renovation.cpp
        src/Catering.cpp
)

# 2. Het echte programma
# Gebruikt main.cpp + alle core bestanden
add_executable(MeetingPlanner src/main.cpp ${CORE_SOURCES})

# --- Google Test setup ---
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 3. De Test Executable
# Gebruikt de test-bestanden + ALLE core bestanden om "undefined references" te voorkomen
add_executable(run_meeting_tests
        tests/RoomTesting.cpp
        tests/DomainTests.cpp
        tests/ParserTests.cpp
        ${CORE_SOURCES}
)

# Link de Google Test bibliotheek
target_link_libraries(run_meeting_tests GTest::gtest_main)
target_include_directories(run_meeting_tests PRIVATE include)

# Zorg dat de XML bestanden beschikbaar zijn in de build map
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input DESTINATION ${CMAKE_CURRENT_BINARY_DIR})