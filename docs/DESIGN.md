**1. Project Overview & Core Loop**

Minishell is a custom implementation of a basic UNIX command-line interpreter. Its primary goal is to parse user input, execute commands (both built-in and external), manage environment variables, and handle shell features like pipes, redirections, and signals, mimicking the behavior of shells like bash.

The core operation revolves around a main loop found in `main.c`.
* **Initialization:** Upon launch, the shell initializes its state, primarily by converting the environment variables provided by the operating system (`envp`) into an internal linked list structure (`t_env`). It also sets up signal handlers for interactive use, ensuring that signals like `SIGINT` (Ctrl+C) and `SIGQUIT` (Ctrl+\) are handled gracefully without terminating the shell itself.
* **Global variable:** The global variable `g_signal_state` is used to track the state of signals. It is set to 0 initially and updated in the signal handler (`set_signal_handler`) to indicate whether a signal has been received.
* **Default environment:** If the program is run without any environment variables, it initializes a default environment with `PATH` set to `/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin`, and `SHLVL` set to 1. This is done in the `create_default_env` function.
* **History management:** The shell uses the `readline` library to manage command history. It initializes the history list and sets up a prompt using `receive_input`.
* **Signal handling:** The shell sets up signal handlers for `SIGINT` and `SIGQUIT` to ensure that the shell can handle user interrupts gracefully. The signal handler (`set_signal_handler`) is defined in `signal_setup.c` and is set up using `set_signal_handler(SIGINT, handle_sigint)` and `set_signal_handler(SIGQUIT, SIG_IGN)`.
* **Input reception:** The shell enters the `ft_main_loop`. Inside this loop, the `receive_input` function uses the `readline` library to display the prompt ("minishell$ ") and read user input. Input validation (`validate_input`) checks for basic syntax errors like unclosed quotes or invalid pipe/redirection sequences before further processing. Valid input is added to the command history.
* **Processing:** Valid input strings are then processed command by command (handling potential multi-line inputs separated by newlines). Each command string undergoes tokenization and parsing.
* **Execution:** The resulting structure (an Abstract Syntax Tree) is executed.
* **Looping:** The loop continues, prompting for new input until an exit condition (e.g., `EOF` or the `exit` command) is met.
* **Termination:** Before exiting, `quit_shell` is called to free allocated resources, notably the environment list, and clear the readline history.

**2. Architecture & key modules**

The project follows a modular design, separating concerns into distinct components:

* **Core** (`core/`): Manages the main shell loop, input reading (`receive_input.c`), exit status (`exit_status.c`), and dynamic buffer management (`dynamic_buffer.c`).
* **Environment** (`env/`): Handles all aspects of environment variable management, including storage (`t_env` linked list), manipulation (setting, getting, unsetting), validation, expansion (`$` variables), and conversion to/from the `char**` format required by `execve`. It also handles quote processing (`env_quote_handling.c`) during variable expansion.
* **Parser** (`parser/`): Responsible for transforming the raw input string into an executable structure.
    * **Tokenizer** (`tokenizer.c`): Breaks the input string into tokens (words, operators like `|`, `<`, `>`). It handles quotes and performs environment variable expansion (`tokenizer_expansion.c`).
    * **AST builder** (`parser_build_ast.c`): Constructs an Abstract Syntax Tree (AST) from the tokens. This tree represents the command structure, including pipes, and redirections. Error handling (`parser_errors.c`) identifies syntax errors during this phase.
* **Executor** (`executor/`): Traverses the AST and executes the commands. It manages process creation (`fork`), pipes (`pipe`), redirections (`dup2`, `open`), built-in execution, and external command execution via `execve`.
* **Builtins** (`builtins/`): Implements shell built-in commands like `cd`, `echo`, `pwd`, `export`, `unset`, `env`, and `exit`.
* **Signals** (`signals/`): Manages signal handling (`SIGINT`, `SIGQUIT`) for different contexts (interactive prompt, heredoc, command execution).
* **Utils** (`utils/`): Contains shared utility functions for string manipulation, memory management, path handling, character checks, number conversions, etc.

**3. Data structures**

Several key data structures underpin Minishell's functionality:

* `t_shell`: The central structure holding the shell's state, including the environment list (`env`), the current exit status (`exit_status`), and a reusable buffer.
* `t_env`: A singly linked list where each node represents an environment variable, storing its `key` and `value` as strings. This allows for efficient addition, removal, and searching of variables.
* `t_ast` / `t_ast_node`: The Abstract Syntax Tree is the core representation of a parsed command.
    * `t_ast` holds the root node and any syntax error information. The decision to keep the syntax error in the `t_ast` structure allows for easy access and handling during execution.
    * `t_ast_node` represents a single node in the tree. It contains:
        * `type`: An enum (`t_node_type`) indicating the node's nature (e.g., `NODE_COMMAND`, `NODE_PIPE`, `NODE_REDIRECTION`, `NODE_SUBSHELL`).
        * `data`: A union (`t_node_data`) holding specific data based on the node type (e.g., `t_command` struct with `name` and `args` for a command, `t_pipe` struct with `left` and `right` child nodes).
        * `next`: Pointer for potentially chaining simple commands (though pipes are typically handled via left/right children).
        * `fd_in`, `fd_out`: File descriptors used during execution, especially for pipes and redirections.
* `t_dynamic_buffer`: A structure used for building strings dynamically, automatically resizing as needed. Useful for processes like environment variable expansion where the final string length isn't known beforehand.
* `t_parser_state`, `t_tokenizer_state`, `t_token_context`: Transient structures used during the parsing and tokenization phases to manage state like the current token index, quote status, and buffer contents.

**4. Execution flow**

1.  **Input & validation:** `receive_input` reads a line. `validate_input` performs preliminary checks for syntax errors (unclosed quotes, invalid pipes/redirections).
2.  **Tokenization:** `tokenize_input` splits the validated input into tokens, respecting quotes. Environment variables (`$VAR`, `$?`) are expanded during `expand_tokens`.
3.  **AST construction:** `build_ast` takes the tokens and constructs the AST. `handle_current_token` iterates through tokens, calling handlers (`handle_command`, `handle_pipe`, `handle_redirection`, etc.) to create and link `t_ast_node`s. Syntax errors detected here are flagged in `ast->syntax_error`.
4.  **Execution:** If the AST is valid (`ast->syntax_error == SYNTAX_OK`), `execute_ast` traverses the tree.
    * **Simple commands:** `handle_node_command` is called. It checks if the command is a built-in. If so, the corresponding function (e.g., `handle_cd`, `handle_echo`) is executed directly within the shell process. If not, `handle_system_cmd` is called.
    * **System commands:** `handle_system_cmd` prepares arguments (`generate_full_command`), resolves the command path (`resolve_command_path` using `find_command_in_path`), `forks` a child process (`create_child_process`), sets up I/O redirection (`setup_child_io`), and calls `execve` in the child. The parent waits for the child (`waitpid`, `wait`) and captures the exit status.
    * **Pipes:** `handle_pipe_node` creates a pipe (`pipe()`), forks, and recursively calls `execute_command` for the left and right sides, connecting them via the pipe's file descriptors. The parent waits for child processes and propagates the exit status of the last command in the pipeline.
    * **Redirections:** Redirection nodes modify the `fd_in` or `fd_out` fields of associated command nodes or directly handle file operations (`open`, `dup2`, `close`). `handle_redirection_node` and its helpers manage this logic, including file opening/creation and writing output to files (`ft_write_fd_to_file`). Heredoc (`<<`) is handled specially, often involving a temporary pipe or file to read the input until the delimiter is found (`handle_heredoc`).
5.  **Output & prompt:** Output from commands is written to `STDOUT_FILENO` (or redirected). After execution, the main loop prompts for the next command.

**5. Coding principles & practices**

* **Modularity:** The codebase is well-structured into directories based on functionality (core, env, parser, executor, builtins, signals, utils), promoting maintainability and separation of concerns. Header files (`inc/`) define interfaces for each module.
* **Error handling:** Errors are handled relatively consistently. `ft_error_msg` is used for standardized error messages. System call failures often use `perror`. Specific exit codes are used (e.g., 1 for general errors, 2 for syntax errors, 126 for permission errors, 127 for command not found). Syntax errors during parsing are tracked via the `t_syntax_error` enum.
* **Memory management:** Significant attention is paid to memory management. `safe_malloc` likely wraps `malloc` with error checking and immediate exit on failure. `safe_free` wraps `free` and sets the pointer to NULL to prevent double frees. Dedicated functions exist for freeing complex structures like the AST (`free_ast_node`, `free_ast`) and the environment list (`free_env_list`). Array freeing (`free_array`) is also handled.
* **Resource management:** File descriptors are carefully managed, especially around pipes and redirections, ensuring they are closed when no longer needed (`close`). Child processes are waited for using `wait` and `waitpid` to prevent zombies.
* **Readability & style:** The code uses comments (including header blocks explaining file purpose) and generally descriptive function/variable names. It adheres to the 42 school coding style.
* **Signal safety:** Signal handlers predominantly use async-signal-safe functions like `write` for output. A `volatile sig_atomic_t` global variable (`g_signal_state`) is used to communicate signal occurrences between the handler and the main program logic.
