# --- Project Definition ---
cmake_minimum_required(VERSION 3.10)
project(LHIG VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Dependencies ---
find_package(Threads REQUIRED)

# --- External Library: open62541 ---
# Do NOT apply strict flags to this
set(UA_ENABLE_AMALGAMATION OFF CACHE BOOL "" FORCE)
set(UA_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(UA_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(third_party/open62541)

# --- Target Definition: lhig_gw ---
add_executable(lhig_gw
    src/main.cpp
    src/legacy_client.cpp
    src/opcua_server.cpp
)

# --- CERN QA: Strict Compiler Flags ---
# Apply strict flags ONLY to our code.
target_compile_options(lhig_gw PRIVATE -Wall -Wextra -Werror -pedantic)

# --- CERN QA: Memory Sanitizer (ASan) ---
option(ENABLE_ASAN "Enable AddressSanitizer" OFF)
if(ENABLE_ASAN)
    target_compile_options(lhig_gw PRIVATE -fsanitize=address -fno-omit-frame-pointer -g)
    target_link_options(lhig_gw PRIVATE -fsanitize=address)
endif()

# --- Include Directories & Linking ---
target_include_directories(lhig_gw PUBLIC include)
target_link_libraries(lhig_gw PRIVATE open62541 Threads::Threads)