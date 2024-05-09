# Krypton Programming Language

Welcome to Krypton, an exciting new programming language that offers versatile features with an emphasis on simplicity and user experience. Right now, Krypton supports a Tree-Walking interpreter, but there are plans to extend this functionality to other options, such as Java bytecode (JAR_FILE) and machine code (EXE_FILE) in the future.

## Features
- Command-line interface
- Simple and friendly C-style Syntax
- Minimal boilerplate
- Supports both Object-Oriented and Functional Programming
- Statically typed with type inference
- Automatic memory management
- Built-in standard library
- Interpreted language

## Future Plans
- Create a package manager for Krypton
- Extend support to Java bytecode
- Add a KVM (Krypton Virtual Machine)
- Extend support to LLVM for machine code
- Add a GUI for Krypton

## Installation

The instructions to build and install Krypton are as follow:

**Prerequisites:**
- A windows machine
- Access to a terminal
- Ability to run executables (.exe files)

**Build:**
- Download the installer from the latest release from the [releases page](https://github.com/Krypton-Lang/Krypton/releases)
- Run the installer and follow the instructions
- Once the installer is finished, you can run Krypton from the command line by typing `krypton`

## Usage

`$ krypton <script> [args]`

Visit the [documentation](https://gitbooks.io/krypton) for more information.

### Hello World Example

`myFirstKryptonScript.kr`
```krypton
import std.io;

void main()
{
    print("Hello World!");
}
```
Execute the script with:

`$ krypton myFirstKryptonScript.kr`


## Contributors

| Name  | Role / Contribution | Discord  |
|-------|---------------------|----------|
| Kyren | Head Developer      | Kyren223 |


## License

Copyright (c) 2023 Krypton. All Rights Reserved.

Redistribution and use in source and binary forms, with or without modification, are not permitted.



## Contact

For any inquiries, please reach out to Kyren223 on discord
For bug reports or feature requests, please open an issue on GitHub.