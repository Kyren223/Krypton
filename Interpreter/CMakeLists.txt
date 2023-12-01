set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/release)

include_directories(include)

# main
add_executable(Interpreter src/core/Interpreter.cpp
        include/cli/ArgumentHandler.h
        include/cli/CommandExecutor.h
        src/cli/ArgumentHandler.cpp
        src/cli/CommandExecutor.cpp)
target_include_directories(Interpreter PRIVATE include/)
set_target_properties(Interpreter PROPERTIES OUTPUT_NAME KryptonInterpreter)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_definitions(Interpreter PRIVATE DEBUG=true)
else ()
    target_compile_definitions(Interpreter PRIVATE DEBUG=false)
endif ()

get_target_property(INTERPRETER_SOURCES Interpreter SOURCES)


# tests
add_executable(InterpreterTests ${INTERPRETER_SOURCES} tests/test.cpp
        tests/ArgumentHandlerTest.cpp)
target_include_directories(InterpreterTests PRIVATE include/)
target_link_libraries(InterpreterTests PRIVATE Catch2::Catch2WithMain)




