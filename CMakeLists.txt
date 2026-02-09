# --- Project Definition ---
cmake_minimum_required(VERSION 3.10)
project(LHIG VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This tells CMake to look inside the submodule's directory for its own CMakeLists.txt
# UA_ENABLE_AMALGAMATION=ON combines the library into a single source file for easier builds.
set(UA_ENABLE_AMALGAMATION ON CACHE BOOL "Enable amalgamation for open62541")
add_subdirectory(third_party/open62541)

# --- Target Definition ---
add_executable(lhig_gw
    src/main.cpp
    src/legacy_client.cpp
    src/opcua_server.cpp
)

# --- Include Directories ---
target_include_directories(lhig_gw PUBLIC 
    include
    ${CMAKE_CURRENT_BINARY_DIR}/third_party/open62541 
)

# --- Linking ---
# This links our executable against the compiled open62541 library.
target_link_libraries(lhig_gw PRIVATE open62541-core)