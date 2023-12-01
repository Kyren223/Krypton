set(SOURCES src/PackageManager.cpp) # src files
set(TEST_SOURCES tests/test.cpp) # test files

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/release)

# main
add_executable(PackageManager ${SOURCES})
target_include_directories(Interpreter PRIVATE include/)
set_target_properties(PackageManager PROPERTIES OUTPUT_NAME "KaPI")

# tests
add_executable(PackageManagerTests ${SOURCES} ${TEST_SOURCES})
target_link_libraries(PackageManagerTests PRIVATE Catch2::Catch2WithMain)
