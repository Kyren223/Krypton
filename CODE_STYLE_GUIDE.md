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
