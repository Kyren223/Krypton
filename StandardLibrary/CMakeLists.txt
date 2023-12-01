set(SOURCES src/main.cpp
        src/main.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/release)

add_library(StandardLibrary ${SOURCES})
set_target_properties(StandardLibrary PROPERTIES OUTPUT_NAME "KryptonSTD")
target_include_directories(StandardLibrary PRIVATE include/)