set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/release)

include_directories(include)
include_directories(src)

# main
add_executable(Interpreter src/Interpreter.cpp
        include/cli/ArgumentParser.h
        include/cli/CommandExecutor.h
        src/cli/ArgumentParser.cpp
        src/cli/CommandExecutor.cpp
        include/cli/Argument.h
        include/common/Constants.h
        src/common/Logger.cpp
        include/common/Logger.h
        src/common/StringHelper.cpp
        include/common/StringHelper.h
        include/parser/Parser.h
        src/lexer/Lexer.cpp
        include/lexer/Lexer.h
        include/nodes/ASTNode.h
        include/runtime/Runtime.h
        src/lexer/Token.cpp
        include/lexer/Token.h
        src/common/FileHelper.cpp
        include/common/FileHelper.h
        src/common/ErrorHandler.cpp
        include/common/ErrorHandler.h
        include/nodes/Expressions.h
        src/parser/Parser.cpp
        src/common/PrettyPrinter.cpp
        include/common/PrettyPrinter.h
        src/types/Value.cpp
        include/types/Value.h
        src/types/Type.cpp
        include/types/Type.h
        include/types/Primitive.h
        src/types/IntType.cpp
        include/types/Operations.h
        src/types/IntType.cpp
        src/types/BoolType.cpp
        src/runtime/KryptonRuntime.cpp
        include/runtime/KryptonRuntime.h
        src/types/DecType.cpp
        src/types/CharType.cpp
        include/nodes/Statements.h
        src/types/StrType.cpp
        src/runtime/Environment.cpp
        include/runtime/Environment.h
        include/common/SourceLocation.h
        src/types/FuncType.cpp
        include/nodes/FunctionNodes.h
)

target_include_directories(Interpreter PRIVATE include/)
set_target_properties(Interpreter PROPERTIES OUTPUT_NAME KryptonInterpreter)

get_target_property(INTERPRETER_SOURCES Interpreter SOURCES)

# tests
add_executable(InterpreterTests ${INTERPRETER_SOURCES}
        tests/ArgumentParserTest.cpp
        tests/LoggerTest.cpp
        tests/CommandExecutorTest.cpp
        tests/FileHelperTest.cpp
        tests/StringHelperTest.cpp
        tests/LexerTest.cpp
        tests/ParserTest.cpp)
target_include_directories(InterpreterTests PRIVATE include/)
target_link_libraries(InterpreterTests PRIVATE Catch2::Catch2WithMain)
target_compile_definitions(InterpreterTests PRIVATE NO_MAIN)


# Debug
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Interpreter PRIVATE DEBUG=true)
    target_compile_definitions(InterpreterTests PRIVATE DEBUG=true)
else ()
    target_compile_definitions(Interpreter PRIVATE DEBUG=false)
    target_compile_definitions(InterpreterTests PRIVATE DEBUG=false)
endif ()




