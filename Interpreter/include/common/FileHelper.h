// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <string>
#include <fstream>
#include <filesystem>
#include <optional>
#include <variant>
#include <vector>

namespace fs = std::filesystem;
using std::string, std::optional, std::streamsize, std::vector, std::ifstream;


enum class PathType
{
    KRYPTON_FILE, // .kr Krypton File
    KRYPTON_AST_FILE, // .kast Krypton Abstract Syntax Tree Binary File
    KRYPTON_BYTECODE_FILE, // .kbc Krypton Bytecode Binary File
    JAR_FILE, // .jar Java Archive File
    EXE_FILE, // .exe Executable File
    DLL_FILE, // .dll Dynamic Link Library File
    NO_EXTENSION, // File with no extension
    UNKNOWN, // Any other file
    DIRECTORY, // Directory
};

class FileHelper
{
public:
    static optional<fs::path> getFileIfExists(const string& path);
    static PathType getPathType(const fs::path& path);
    static string getFileName(const fs::path& path);
    static string trimExtension(const string& file);
    static optional<string> readFile(const fs::path& path);
    static void writeFile(const fs::path& path, const string& data);
};

