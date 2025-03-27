cmake_minimum_required(VERSION 3.28.3)
project(TerminalUtilities)

set(CMAKE_CXX_STANDARD 20)

# Define the static library
add_library(TerminalUtilities STATIC
        src/TerminalUtilities.cpp
        src/SelectionMenu.cpp)

# Specify where the headers are located
target_include_directories(TerminalUtilities PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Install the static library to /usr/local/lib/cpp
install(TARGETS TerminalUtilities
        DESTINATION /usr/local/lib/cpp/terminalUtilities/src)

# Install the header files to /usr/local/include/cpp
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
        DESTINATION /usr/local/lib/cpp/terminalUtilities/include
        FILES_MATCHING PATTERN "*.h")
