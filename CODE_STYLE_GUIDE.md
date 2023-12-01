# Krypton Code Style Guide

This document outlines the coding style conventions used in the Krypton project. Adherence to this guide helps ensure code consistency and readability across the project.

## Naming Conventions

- Folders: snake_case. For example, `parsing_module`.
- Namespaces: lowercase. For example, `filehelper`.
- Classes/Structures: PascalCase. For example, `MyAwesomeClass`.
- Variables/Functions: camelCase. For example, `myMemoryLeakerVariable`, `myForgotToReleaseMemoryFunction()`.
- Constants/Enum Values: SCREAMING_SNAKE_CASE. For example, `CONSTANT_VALUE`, `ENUM_TYPE_1`.

## Indentation

Use 4 spaces for indentation.

## Code Blocks

Braces are always in a new line
You may avoid braces if:
- There is only 1 statement
- The statement can fit on the same line
Otherwise you should use braces

## C++
- Use `nullptr` instead of `NULL`
- Use `#pragma once` instead of include guards
- Use only `#include <header>`
- If a function can be marked as `const`, do it
- Use `const` whenever possible

## File Structure
- All source files should be in the `src` folder
- All header files should be in the `include` folder
- Headers end with `.h`
- Source files end with `.cpp`
- Header files with implementation should end with `.hpp`
- All files should be named using PascalCase
- All folders should be named using snake_case

