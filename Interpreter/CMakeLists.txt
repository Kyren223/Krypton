set(SOURCES ) # src files
set(TEST_SOURCES tests/test.cpp) # test files

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/release)

# main
add_executable(Interpreter src/core/main.cpp ${SOURCES})
target_include_directories(Interpreter PRIVATE include/)
set_target_properties(Interpreter PROPERTIES OUTPUT_NAME "KryptonInterpreter")

# tests
add_executable(InterpreterTests ${SOURCES} ${TEST_SOURCES})
target_link_libraries(InterpreterTests PRIVATE Catch2::Catch2WithMain)


