# Minishell

## Table of Contents
- [Introduction](#introduction)
- [Objectives](#objectives)
- [Features](#features)
- [Technologies Used](#technologies-used)
- [Project Structure](#project-structure)
- [Installation and Compilation](#installation-and-compilation)
- [Usage](#usage)
- [Bonus Features](#bonus-features)
- [Troubleshooting](#troubleshooting)
- [Resources](#resources)

---

## Introduction
Minishell is a project from the **42 School** curriculum designed to implement a simple shell in **C**, replicating some behavior of the Unix shell. The goal is to deepen the understanding of process creation, file descriptors, signals, and system calls.

## Objectives
- Learn how a shell interacts with the operating system.
- Implement built-in commands and support external commands.
- Manage pipes, redirections, and environment variables.
- Handle signals like **CTRL+C**, **CTRL+D**, and **CTRL+\**.
- Ensure memory management with proper error handling.

## Features
- Command execution (both built-in and external commands).
- **Pipes (`|`)** and **Redirections (`>`, `<`, `>>`, `<<`)**.
- Environment variables and `$PATH` handling.
- Signal handling for **SIGINT, SIGQUIT, and EOF**.
- Interactive mode with a custom prompt.

## Technologies Used
- **C**
- **POSIX System Calls** (fork, execve, waitpid, dup2, pipe, etc.)
- **GNU Readline Library** (optional, for input handling)

## Project Structure
```
minishell/
├── src/
│   ├── builtins/
│   │   ├── cd.c
│   │   ├── echo.c
│   │   ├── env.c
│   │   ├── exit.c
│   │   ├── export.c
│   │   ├── pwd.c
│   │   ├── unset.c
│   ├── execution/
│   │   ├── exec.c
│   │   ├── pipes.c
│   │   ├── redirections.c
│   ├── parsing/
│   │   ├── lexer.c
│   │   ├── parser.c
│   ├── signals/
│   │   ├── signals.c
│   ├── main.c
├── include/
│   ├── minishell.h
├── Makefile
├── README.md
```

## Installation and Compilation
### Prerequisites
- **GNU Make** and **GCC**
- **GNU Readline** (optional)

### Steps
1. Clone the repository:
   ```sh
   git clone https://github.com/abdellah-archtouy/minishell.git
   cd minishell
   ```
2. Compile the project:
   ```sh
   make
   ```
3. Run the shell:
   ```sh
   ./minishell
   ```

## Usage
- Run commands as in a standard shell:
  ```sh
  ls -l | grep minishell > output.txt
  ```
- Built-in commands:
  ```sh
  echo Hello, World!
  cd /home/user
  pwd
  export VAR=value
  unset VAR
  env
  exit
  ```
- Handle **CTRL+C** (interrupt), **CTRL+D** (EOF), and **CTRL+\** (quit).

## Bonus Features
- **Wildcard expansion (`*`)**
- **Command history**
- **Advanced error handling and syntax checks**
- **More built-ins and extra utilities**

## Troubleshooting
- If compilation fails, check dependencies like `readline`.
- Use `make clean` before recompiling.
- Debug execution using `gdb` or `valgrind` for memory leaks.

## Resources
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/)
- [Linux System Calls](https://man7.org/linux/man-pages/)
- [42 School's Minishell Subject](https://github.com/42School/minishell)

