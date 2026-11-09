# Vole-machine-simulator
This repo is made for Assignment 2 for OOP


PROJECT NAME: Vole Machine Simulator (CLI & GUI)
COURSE: Object-Oriented Programming (OOP) - Assignment 2
=========================================================

1. PROJECT OVERVIEW
-------------------
This project is a simulator of the Vole machine, a simple educational computer
with 16 general-purpose registers (R0 - RF) and 256 bytes of memory
(addresses 00 - FF). Each instruction is 2 bytes (4 hex digits).

The simulator is built from separate classes: Machine, CPU, ALU, Memory,
RegisterBank, Screen, ProgramLoader, MainMenu (CLI) and MainWindow (GUI).

It is delivered as ONE executable (VoleSimulator) with two modes:
1. GUI Mode (default): A desktop application built with Qt Widgets. It shows
   the 16x16 memory grid, the register table, PC / IR / CPU status, the
   screen output and an event log, with buttons for Load, Step, Run, Reset
   and Clear operations.
2. CLI Mode (run with the --cli flag): A text menu in the terminal for
   loading a program, editing memory/registers, running all at once, and
   executing step by step.


2. SUPPORTED INSTRUCTIONS
-------------------------
Format: each instruction is 4 hex digits, OPRS / OPRXY (R, S, T, X, Y = one hex digit).

  1RXY  LOAD   register R with the contents of memory cell XY
  2RXY  LOAD   register R with the immediate value XY
  3RXY  STORE  register R into memory cell XY
               (writing to address 00 or FF also prints the byte on the Screen)
  40RS  MOVE   copy register R into register S
  5RST  ADD    R = S + T (two's complement integers)
  6RST  ADD    R = S + T (floating point, 8-bit format)
  7RST  OR     R = S OR T
  8RST  AND    R = S AND T
  9RST  XOR    R = S XOR T
  AR0X  ROTATE register R right by X bits
  BRXY  JUMP   to address XY if register R equals register 0
  C000  HALT   stop execution

Program file format (see src/sample_program.txt):
* One or more instructions per line, written as hex digits.
* Comments start with ; or # or //
* Whitespace and an optional 0x prefix are ignored.
* The start address must be even, between 00 and FE.


3. TOOLS & VERSIONS USED
------------------------
To successfully compile, build, and run both modes of the program, the
following tools and versions were used during development:

* Programming Language: C++ (Standard: C++17)
* Compilers:
  - GCC (GNU Compiler Collection) v11.2+ (Linux / MinGW on Windows) or MSVC (Microsoft Visual C++ 2022)
* Build System:
  - CMake (v3.16 or higher) / QMake
* IDE / Framework:
  - Qt Creator (v10.0 or higher)
  - Qt Framework (Qt 6.x or Qt 5.15+) - Qt Widgets module
* Operating System Tested: Windows 11 / Ubuntu 22.04 LTS


4. PREREQUISITES
----------------
Before running the project, ensure you have the following installed on your system:
* A C++17 compatible compiler (e.g., MinGW for Windows, GCC for Linux, or MSVC).
* Qt Creator with the appropriate Qt Kit installed (matching your compiler version).
  Both the GUI and CLI modes need the Qt libraries, because they share one executable.
* CMake (if building via CMakeLists.txt).


5. PROJECT STRUCTURE (src/)
---------------------------
  main.cpp                   Entry point: GUI by default, CLI with --cli
  Machine.h / .cpp           Ties the CPU, memory, registers, screen and ALU together
  CPU.h / .cpp               Fetch-decode-execute cycle, PC, IR, halt state
  ALU.h / .cpp               Arithmetic and logic operations
  Memory.h / .cpp            256-cell memory
  RegisterBank.h / .cpp      16 registers
  Screen.h / .cpp            Output buffer
  ProgramLoader.h / .cpp     Reads program files into memory
  MainMenu.h / .cpp          CLI menu
  MainWindow.h / .cpp / .ui  Qt GUI
  CMakeLists.txt             CMake build file
  VoleSimulator.pro          QMake build file
  sample_program.txt         Example program (prints "HI" on the screen)
  *.puml                     PlantUML GUI class and sequence diagrams


6. HOW TO SET UP AND RUN
------------------------

PART A: Building the Program (Qt Creator)
1. Launch Qt Creator.
2. Go to File > Open File or Project and select the CMakeLists.txt (or
   VoleSimulator.pro) file inside the src folder.
3. Configure the project by selecting your installed Qt Kit (e.g., Desktop Qt 6.x MinGW or GCC).
4. Click the Configure Project button.
5. Build the project by pressing Ctrl + B (or clicking the hammer/Build icon in the bottom left).

PART B: Running the GUI Program
1. Press Ctrl + R in Qt Creator (or the green Play icon), or run the built
   executable with no arguments.
2. Click Load and choose a program file (for example src/sample_program.txt).
   Set the start address (hex, even number) first; the default is 00.
3. Click Step to execute one instruction, or Run to execute until the CPU halts
   (Run stops automatically after 50000 steps to guard against infinite loops).
4. Use the Set Memory / Set Register boxes to edit values, or click a cell/row
   in the tables to select it. Reset restarts the CPU at the start address;
   Clear All wipes the CPU, memory, registers and screen.

PART C: Running the CLI Program
1. Build the project as in Part A (or from a terminal, see below).
2. Open your terminal (Linux/macOS) or Command Prompt/PowerShell (Windows).
3. Run the executable with the --cli flag:
   ./VoleSimulator --cli
   (On Windows: VoleSimulator.exe --cli)
4. Use the menu:
   1. Load program from file    (enter the file path, then an even hex start address)
   2. Memory / Register operations (overwrite a cell or register, clear, full reset)
   3. Run program all at once
   4. Execute step by step
   5. Display machine state
   6. Exit

Optional: building from the terminal with CMake
   cd path/to/src
   mkdir build && cd build
   cmake ..
   cmake --build .
   ./VoleSimulator          (GUI)
   ./VoleSimulator --cli    (CLI)

   If CMake cannot find Qt, point it at your Qt install:
   cmake .. -DCMAKE_PREFIX_PATH=/path/to/Qt/6.x/gcc_64


7. SAMPLE PROGRAM
-----------------
src/sample_program.txt loads 5 and 3 into registers, adds them, stores the
result in memory cell 20, then writes 'H' and 'I' to the screen and halts.
After running it, the Screen shows:  HI


First Part1 video
https://youtu.be/I-tGk0gv1uA





document Link:
https://docs.google.com/document/d/1M5WozAdExF89liL5HkimA5tTftP0Q1MQAEBU8LLKcNc/edit?tab=t.0

GitHub Link:
https://github.com/Ahmed666Mahmoud/Vole-machine-simulator.git
