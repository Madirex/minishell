# Minishell

A custom implementation of a basic UNIX command-line interpreter, built in C. This project aims to replicate core functionalities of shells like bash, including command execution, pipes, redirections, environment variable management, and signal handling.

## Overview

Minishell parses user input, builds an internal representation (Abstract Syntax Tree), and executes the commands accordingly. It handles both external commands found in the system's `PATH` and a set of built-in commands.

## Features

* **Command execution:** Executes external commands located via the `PATH` environment variable using `fork` and `execve`.
* **Built-in sommand:** Implements essential shell built-ins (see list below).
* **Pipes (|):** Allows chaining commands, where the standard output of one command is connected to the standard input of the next.
* **Redirections:**
    * Input redirection (<): Reads input for a command from a file.
    * Output redirection (>): Writes command output to a file, overwriting it.
    * Append output redirection (>>): Appends command output to a file.
    * Heredoc (<<): Reads input from the current source until a specific delimiter is encountered.
* **Environment variables:**
    * Manages environment variables internally using a linked list.
    * Supports variable expansion (`$VAR`, `$?`).
    * Initializes environment from the system environment (`envp`).
    * Handles `SHLVL` incrementation.
* **Signal handling:**
    * Handles `SIGINT` (Ctrl+C) gracefully in interactive mode (new prompt) and during heredoc (cancels heredoc).
    * Ignores `SIGQUIT` (Ctrl+\) in interactive mode.
    * Child processes handle signals with default behavior.
* **Command history:** Uses the `readline` library for input reading, providing command history navigation (up/down arrows).
* **Quotes handling:** Correctly processes single and double quotes, affecting tokenization and variable expansion.

## Installation & compilation

**Prerequisites:**

* A C compiler (like `gcc` or `clang`)
* `make`
* `readline` library (development headers might be needed, e.g., `libreadline-dev` or `readline-devel`)

**Compilation:**

1.  Clone the repository (or ensure you have the source code).
2.  Navigate to the project's root directory.
3.  Run `make`. This should compile the source files and create the `minishell` executable.

```bash
git clone <repository_url> minishell
cd minishell
make
```

## Usage

After successful compilation, run the shell:

```bash
./minishell
```

You will be presented with the `minishell$` prompt. Type commands as you would in a standard shell. Use `Ctrl+D` or the `exit` command to terminate Minishell.

## Architecture overview

The project is structured modularly:

* **`core/`**: Handles the main loop, input reading, and core shell state.
* **`parser/`**: Contains the tokenizer (splitting input into tokens) and the parser (building the Abstract Syntax Tree).
* **`ast/`**: Defines the Abstract Syntax Tree (AST) structures (`t_ast`, `t_ast_node`) and provides functions for creating and freeing AST nodes.
* **`executor/`**: Responsible for traversing the AST and executing commands, handling pipes, redirections, and process management.
* **`builtins/`**: Implements the shell's built-in commands.
* **`env/`**: Manages environment variables (storage, retrieval, expansion, conversion).
* **`signals/`**: Configures and handles POSIX signals.
* **`utils/`**: Provides common utility functions (string manipulation, memory management, path searching, etc.).
* **`inc/`**: Contains all header files defining interfaces and data structures.

You can generate the full developer documentation locally. Go to [update.md](docs/update.md) for indications.
 

## Built-in commands

The following built-in commands are implemented:

* `echo`: Prints arguments to standard output (supports `-n` flag).
* `cd`: Changes the current working directory. Handles `~` and `-`.
* `pwd`: Prints the current working directory.
* `export`: Sets or displays environment variables. With no arguments, lists variables in a specific format.
* `unset`: Removes environment variables.
* `env`: Prints the current environment variables.
* `exit`: Terminates the minishell process (supports optional exit status argument).

## Technical details

For a detailed design overview and architecture breakdown, see [DESIGN.md](docs/DESIGN.md).

* **Parsing:** Input is tokenized and then parsed into an Abstract Syntax Tree (AST). The AST represents the command structure, including pipes and redirections, facilitating structured execution.
* **Execution:** Uses `fork`, `execve`, `pipe`, `dup2`, `wait`, and `waitpid` system calls to manage processes and I/O for external commands and pipelines. Built-ins are executed directly within the shell process where appropriate (`cd`, `exit`, `export`, `unset`).
* **Environment:** Stored internally as a linked list (`t_env`) for efficient manipulation.
* **Input:** Uses the `readline` library for interactive input editing and history.
* **Signals:** Uses `sigaction` for robust signal handling.

## Lessons learned
For a review of my learning process, see [LESSONS.md](docs/LESSONS.md).

## Authors

- [Leroidubuffet](https://github.com/leroidubuffet/)
- [Madirex](https://github.com/madirex/)
