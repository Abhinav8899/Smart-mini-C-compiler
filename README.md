# Enhanced Front-End Design of a Mini-Compiler

**Authors:** Abhinav & Aditya Singh  
**Status:** Phase 2 Complete (Front-End & Middle-End)

---

## 📌 Project Overview
This project is a custom, production-grade compiler architecture built using **C, Flex (Lexical Analysis), and Bison (Syntax Analysis)**. It translates a high-level, C-like programming language into an optimized Intermediate Representation (IR) known as Three-Address Code (TAC).

Moving beyond standard academic compilers, this project prioritizes **modern Developer Experience (DX)** and robust memory management, featuring a scoped symbol table, AI-assisted heuristic error correction, in-place constant folding, and precise source-pointer diagnostics.

---

## 🚀 Key Features

### 1. Developer Experience (DX) & Tooling
* **Source Pointer Diagnostics:** Tracks line and column numbers to display precise error locations with caret (`^`) indicators directly under the faulty source code, mirroring tools like Clang and Rust.
* **"Did you mean?" Heuristics:** Implements a Levenshtein Distance algorithm to detect typos in undeclared variables/arrays and actively suggests the closest matching identifier.
* **Smart Semantic Warnings:** Provides helpful hints (e.g., "Implicit int -> float conversion. Consider using a cast") instead of crashing abruptly.
* **CLI Inspection Tools:** Supports command-line flags (`--dump-ast`, `--dump-tac`) to use the compiler as a modular debugging tool.

### 2. Advanced Semantic Analysis
* **Scoped Symbol Tables:** Utilizes a *Stack of Hash Tables* (`push_scope()` / `pop_scope()`) to perfectly handle block-local variables, function parameters, and variable shadowing without memory collisions.
* **Syntactic Desugaring:** Automatically simplifies compound assignments (`+=`, `-=`, `*=`, `/=`) and increment operators (`++`, `--`) at the parser level to keep the AST highly optimized.
* **Strict Type Systems:** Enforces logical operator guards, function parameter validation, implicit type coercion (with warnings), and explicit user casts `(int)`, `(float)`, etc.

### 3. The Optimization Engine (Middle-End)
* **Constant Folding:** A recursive AST pass that pre-calculates static arithmetic (e.g., `3 + 5 -> 8`) and boolean logic in-place before generating intermediate code.
* **Dead Code Elimination:** Automatically prunes unreachable AST branches.
* **Three-Address Code (TAC):** Translates the optimized AST into a linear sequence of machine-agnostic instructions (assignments, jumps, labels, function calls) via a custom `TACList` engine.

---

## 🛠️ Language Specification

This compiler supports a rich, C-like syntax:
* **Data Types:** `int`, `float`, `bool`, `string`, `void`.
* **Control Flow:** `if`, `else if`, `else`, `switch` / `case` / `default`.
* **Loops:** `for`, `while`, `do-while` (with `break` and `continue`).
* **Advanced Structures:** Single-dimensional arrays (`int arr[5];`), scoped execution blocks, and function declarations/calls (`func`).

---

## 📂 Architecture & File Structure

The repository only contains handwritten source code. Generated tool files are managed locally via the Makefile.

* **`lexer.l`**: The Flex scanner. Defines regex rules, tracks column numbers, and buffers source lines for the error pointer.
* **`parser.y`**: The Bison parser. Defines the Context-Free Grammar (CFG), operator precedence, desugaring logic, and constructs the AST.
* **`compiler_utils.h` / `.c`**: The backbone of the compiler. Defines the AST node structures, manages the Scoped Symbol Table stack, handles Levenshtein distance calculations, and manages the TAC engine.
* **`semantic.h` / `.c`**: The "Meaning Maker." Walks the AST for strict type checking, executes the constant folding passes, and generates/prints the final TAC.
* **`main.c`**: The entry point that glues the pipeline together.
* **`setup.fish`**: Local environment configuration script for Arch Linux users.
* **`tests/`**: Directory containing `.txt` files with valid and intentionally broken code to test the compiler's robustness.

---

## 💻 Build & Usage

### Prerequisites
* GCC (GNU Compiler Collection)
* Flex
* Bison
* Make

### Building the Compiler
To build the project, simply use the provided `Makefile`. This will generate the necessary Flex/Bison files and compile the executable.
```bash
make
