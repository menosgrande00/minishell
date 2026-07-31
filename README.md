[README.md](https://github.com/user-attachments/files/27306040/README.md)
# 🐚 Minishell: A Unix Shell in C

![C](https://img.shields.io/badge/language-C-blue.svg)
![Unix](https://img.shields.io/badge/environment-Unix-lightgrey.svg)
![Make](https://img.shields.io/badge/build-Make-green.svg)

*This project has been created as part of the 42 curriculum by oonal, agurses.*

## 📌 Overview
Minishell is a custom, lightweight Unix shell built from scratch in C. The primary objective of this project was to dive deep into the core mechanics of an operating system by recreating the functionality of the bash shell. 

This project goes beyond simple string manipulation; it requires a robust architecture involving **lexical analysis, parsing, Abstract Syntax Trees (AST) or token lists, process creation (`fork`), inter-process communication (`pipe`), and signal handling**.

## 🧠 What I Learned (The Technical Core)
Building a shell from the ground up provided invaluable experience in system-level programming:
* **Process Management:** Mastered the use of `fork`, `execve`, `waitpid`, and understanding parent-child process dynamics.
* **Inter-Process Communication (IPC):** Implemented pipelines (`|`) to seamlessly route the standard output of one command into the standard input of the next.
* **File Descriptors & I/O:** Handled file descriptor duplication (`dup`, `dup2`) for complex input/output redirections (`<`, `>`, `<<`, `>>`).
* **Signal Handling:** Configured custom signal handlers using `sigaction` to ensure the shell behaves like Bash during `SIGINT` (ctrl-C), `EOF` (ctrl-D), and `SIGQUIT` (ctrl-\\) interruptions.
* **Memory Management:** Enforced strict memory leak prevention throughout the lexer, parser, and execution cycles.

## ✨ Features

### 1. Command Execution & Path Resolution
* Executes system binaries by searching through the `PATH` environment variable.
* Supports execution via absolute and relative paths.

### 2. Built-in Commands
Fully custom implementations of standard shell built-ins:
* `echo` (with `-n` flag support)
* `cd` (navigating relative/absolute paths)
* `pwd` (print working directory)
* `export` & `unset` (environment variable management)
* `env` (displaying the environment)
* `exit` (terminating the shell with specific exit codes)

### 3. Parsing and Expansion
* **Quotes:** Accurately handles single quotes (`'`) to disable metacharacter interpretation, and double quotes (`"`) which allow only environment variable expansion (`$`).
* **Environment Variables:** Dynamically expands variables (e.g., `$USER`) and handles the special `$?` variable to retrieve the exit status of the last executed command.

## 🛠️ Installation & Usage

### Prerequisites
* `gcc` or `clang` compiler
* `make`
* GNU `readline` library

### Compiling the Shell
Clone the repository and run `make`. The Makefile is configured to compile the source files rigorously with `-Wall -Wextra -Werror` flags.

```bash
git clone <git@github.com:menosgrande00/minishell.git>
cd minishell
make
```

### Running the Shell
Once compiled, you can start the shell by running the executable:

```bash
./minishell
```
