// Copyright (c) 2023 Krypton. All rights reserved.
#include <common/FileHelper.h>


optional<fs::path> FileHelper::getFileIfExists(const string& path)
{
    fs::path file = path;
    if (!fs::exists(file)) return {};
    if (fs::is_directory(file)) return {};
    return file;
}

PathType FileHelper::getPathType(const fs::path& path)
{
    if (fs::is_directory(path)) return PathType::DIRECTORY;
    if (path.extension() == ".kr") return PathType::KRYPTON_FILE;
    if (path.extension() == ".kast") return PathType::KRYPTON_AST_FILE;
    if (path.extension() == ".kbc") return PathType::KRYPTON_BYTECODE_FILE;
    if (path.extension() == ".jar") return PathType::JAR_FILE;
    if (path.extension() == ".exe") return PathType::EXE_FILE;
    if (path.extension() == ".dll") return PathType::DLL_FILE;
    if (path.extension() == "") return PathType::NO_EXTENSION;
    return PathType::UNKNOWN;
}

string FileHelper::getFileName(const fs::path& path)
{
    return path.filename().string();
}

string FileHelper::trimExtension(const string& file)
{
    return file.substr(0, file.find_last_of('.'));
}

optional<string> FileHelper::readFile(const fs::path& path)
{
    ifstream file(path, std::ios::in | std::ios::binary);
    if (!fs::exists(path) || !file) return {};
    string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return data;
}

void FileHelper::writeFile(const fs::path& path, const string& data)
{
    ofstream file(path, std::ios::out | std::ios::trunc);
    if(file.fail()) throw std::runtime_error("Failed to write to file at " + path.string());
    file << data;
    file.close();
}


