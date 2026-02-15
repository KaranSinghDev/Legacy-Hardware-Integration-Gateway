# --- Project Definition ---
cmake_minimum_required(VERSION 3.10)
project(LHIG VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

# --- Add open62541 Dependency ---
# CRITICAL CHANGE: Turn Amalgamation OFF. Use standard headers.
set(UA_ENABLE_AMALGAMATION OFF CACHE BOOL "" FORCE)
set(UA_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(UA_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)

add_subdirectory(third_party/open62541)

# --- Target Definition ---
add_executable(lhig_gw
    src/main.cpp
    src/legacy_client.cpp
    src/opcua_server.cpp
)

# --- Include Directories ---
target_include_directories(lhig_gw PUBLIC include)

# --- Linking ---
# Linking against 'open62541' automatically handles the include paths for us now
target_link_libraries(lhig_gw PRIVATE open62541 Threads::Threads)