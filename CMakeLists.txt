
cmake_minimum_required(VERSION 3.10)
project(CacheServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include headers
include_directories(include)

# Define source files
set(SOURCES
    src/main.cpp
    src/LRUCache.cpp
)

# Create executable
add_executable(cache_server ${SOURCES})

# Link threading library
find_package(Threads REQUIRED)
target_link_libraries(cache_server PRIVATE Threads::Threads)
