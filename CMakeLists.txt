# --- Project Definition --- 
# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Defines the project name and the C++ version
project(LHIG VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Target Definition ---
# Creates an executable named "lhig_gw" from our source files
add_executable(lhig_gw
    src/main.cpp
    src/legacy_client.cpp
    src/opcua_server.cpp
)

# --- Include Directories ---
# Tells the compiler where to find our header files (.hpp)
target_include_directories(lhig_gw PUBLIC include)