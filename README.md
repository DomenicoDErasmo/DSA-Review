Self-study of data structures and their corresponding algorithms/operations

## Features

### Currently Added
- Linked List
- Double Linked List
- Binary Tree
- Stack
- Queue

### To Add
- Graphs
- Hash Map
- Graph Algorithms
- Visualization of algorithms?

## Prerequisites
- Make (from MinGW)
- clang++ (from LLVM or MinGW)

## Repository Structure

- .vscode: Information for VS Code to run smoothly
- bin: Where the binaries (.exe) and debug (.ilk, .pdb) files get stored
    - Note: Must compile before these appear
- build: Contains .bat scripts and Makefiles for 
    cleaning/running for the src and testing modules
- doc: Contains overhead documentation
- obj: Contains .o files created by the linker
    - Note: Must compile before these appear
- src: Contains source code for the data structures
- testing: Contains unit tests for the data structures

## Build
- Supports the following options:
    - Build src folder
    - Clean src folder
    - Build testing folder
    - Clean testing folder
    - Build all
    - Clean all
- Can run with a preset build task in VS Code with Ctrl-B
- If not using VS Code, you can build/clean all by running 
    .\build\build(clean)_all.bat
- If you want to run a build task for either src or testing,
    refer to .\\.vscode\\tasks.json for examples

## Run Options
- Run or debug mode for either the src folder or testing folder
- You can either click the "Run and Debug" option on VS Code's sidebar to 
    choose the src or testing file to run, 
    or you can simply type .\bin\src.exe (or testing)
- Hotkey to run in VS Code: Ctrl+F5. Hotkey to debug in VS Code: F5.
    - If running in debug mode, be sure to set breakpoints!
