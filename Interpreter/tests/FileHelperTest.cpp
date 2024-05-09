// Copyright (c) 2023 Krypton. All rights reserved.
#include <catch2/catch_test_macros.hpp>
#include <common/FileHelper.h>
#include <filesystem>
#include <fstream>

using namespace std::filesystem;
using std::fstream;

TEST_CASE("FileHelper")
{
    // Create files
    create_directory("C:/Krypton/Interpreter/tests/test_files");
    string file1 = "C:/Krypton/Interpreter/tests/test_files/file1.txt";
    string file2 = "C:/Krypton/Interpreter/tests/test_files/file2.kr";
    string file3 = "C:/Krypton/Interpreter/tests/test_files/file3.dll";
    string file4 = "C:/Krypton/Interpreter/tests/test_files/file4";
    
    path p1 = file1;
    path p2 = file2;
    path p3 = file3;
    path p4 = file4;
    
    SECTION("getFileIfExists")
    {
        REQUIRE(FileHelper::getFileIfExists(file1).has_value() == false);
        REQUIRE(FileHelper::getFileIfExists(file2).has_value() == true);
        REQUIRE(FileHelper::getFileIfExists(file3).has_value() == true);
        REQUIRE(FileHelper::getFileIfExists(file4).has_value() == false);
    }
    
    SECTION("getFileName")
    {
        REQUIRE(FileHelper::getFileName(p1) == "file1.txt");
        REQUIRE(FileHelper::getFileName(p2) == "file2.kr");
        REQUIRE(FileHelper::getFileName(p3) == "file3.dll");
    }
    
    SECTION("getPathType")
    {
        REQUIRE(FileHelper::getPathType(p1) == PathType::UNKNOWN);
        REQUIRE(FileHelper::getPathType(p2) == PathType::KRYPTON_FILE);
        REQUIRE(FileHelper::getPathType(p3) == PathType::DLL_FILE);
        REQUIRE(FileHelper::getPathType(p4) == PathType::NO_EXTENSION);
    }
    
    SECTION("trimExtension")
    {
        REQUIRE(FileHelper::trimExtension(FileHelper::getFileName(p1)) == "file1");
        REQUIRE(FileHelper::trimExtension(FileHelper::getFileName(p2)) == "file2");
        REQUIRE(FileHelper::trimExtension(FileHelper::getFileName(p3)) == "file3");
        REQUIRE(FileHelper::trimExtension(FileHelper::getFileName(p4)) == "file4");
    }
    
    SECTION("writeFile")
    {
        FileHelper::writeFile(file2, "Hello World!");
        FileHelper::writeFile(file3, "ICUP");
    }
    
    SECTION("readFile")
    {
        REQUIRE(!FileHelper::readFile(file1));
        optional<string> contents = FileHelper::readFile(file2);
        REQUIRE(contents);
        REQUIRE(contents== "Hello World!");
        contents = FileHelper::readFile(file3);
        REQUIRE(contents);
        REQUIRE(contents == "ICUP");
        REQUIRE(!FileHelper::readFile(file4));
    }
}