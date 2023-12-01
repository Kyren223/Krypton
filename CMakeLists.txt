cmake_minimum_required(VERSION 3.26)
project(Krypton)

set(CMAKE_CXX_STANDARD 20) # C++20
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  -static -static-libgcc -static-libstdc++")

# Modules
add_subdirectory(Interpreter)
add_subdirectory(PackageManager)
#add_subdirectory(StandardLibrary)

# Tests
# Fetch Catch2
Include(FetchContent)
FetchContent_Declare(
        Catch2
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.4.0.tar.gz
)
FetchContent_MakeAvailable(Catch2)

