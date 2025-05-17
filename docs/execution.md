# Minishell notes: execution

The execution process starts after the parser has successfully built an Abstract Syntax Tree (AST) representing the user's command. The main entry point is the `execute_ast` function.

1.  **AST Traversal Initiation (`execute_ast`):**
    * This function receives the root of the AST (`ast->root`) and the shell state (`t_shell *shell`).
    * It checks the type of the root node.
        * If the root is a `NODE_PIPE`, it calls `execute_command` to handle the pipeline execution, waits for all child processes using `wait_for_children`, and sets the shell's exit status to the status of the last command in the pipe.
        * If the root is not a pipe (likely a `NODE_COMMAND` or `NODE_REDIRECTION`), it iterates through the linked list of nodes starting from the root (using `current = current->next`), executing each logical command sequence using `execute_single_command`.

2.  **Recursive Execution (`execute_command`):**
    * This is the core recursive function that traverses the AST. It takes a pointer to a node (`t_ast_node **node`) and the shell state.
    * It determines the node's type and calls the appropriate handler:
        * **`NODE_PIPE`:** Calls `handle_pipe_node`.
        * **`NODE_COMMAND`:** Calls `handle_command_node`.
        * **`NODE_REDIRECTION`:** Calls `handle_redirection_node`.
    * It returns a file descriptor, which typically represents the standard output of the executed command or pipeline segment, to be used as standard input for the next segment if applicable. Returns -1 on error or if output wasn't captured.

3.  **Handling Simple Commands (`handle_command_node`, `handle_node_command`):**
    * `handle_node_command` is the primary function here.
    * It first checks if the command is a **built-in** (`is_builtin_command`).
        * If it's a built-in (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`), it calls `handle_builtin_command`, which dispatches to the specific built-in function (e.g., `handle_cd`, `handle_pwd`).
        * Built-ins are generally executed directly within the main shell process (exceptions like `cd`, `export`, `unset`, `exit` *must* run in the parent to affect its state).
        * Built-ins that produce output (like `pwd`, `env`, `echo`) might write directly to the appropriate output file descriptor (`node->fd_out`) or, in some cases in this implementation, format output into a string and return a readable file descriptor using a pipe (`get_fd_from_str`) if the output needs to be piped.
    * If it's not a built-in, it's treated as a **system command** and `handle_system_cmd` is called.

4.  **Handling System Commands (`handle_system_cmd`):**
    * **Prepare:** It generates the command arguments array (`generate_full_command`) and resolves the full path of the executable using the `PATH` environment variable (`resolve_command_path`, `find_command_in_path`). Quote handling (`handle_quotes`) is applied to arguments.
    * **Fork:** It creates a child process using `fork()` (`create_child_process`). Original signal handlers for SIGINT/SIGQUIT are ignored in the parent temporarily and restored to default in the child.
    * **Child Process:**
        * Sets up I/O: Redirects standard input and standard output using `dup2` based on the `fd_in` provided and whether it's part of a pipe (`setup_child_io`). For example, if `fd_in` is a pipe read end, `STDIN_FILENO` is `dup2`'d to it. If output needs to go to a pipe, `STDOUT_FILENO` is `dup2`'d to the pipe write end.
        * Executes: Calls `execve` with the resolved path, arguments, and a `char **` version of the environment (`env_to_array`).
        * Error Handling: If `execve` fails, it prints errors (e.g., "Permission denied", "command not found") and exits with appropriate status codes (126, 127).
    * **Parent Process:**
        * Closes unused pipe ends (if applicable).
        * If the command is *not* part of a larger pipeline (`is_pipe` is false), it waits for the specific child using `waitpid` and updates the shell's exit status (`shell->exit_status`) based on the child's termination status.
        * If the command *is* part of a pipeline, it returns the read end of the output pipe (`pipe_fds[0]`) for the next command, and the final waiting happens later.
    * Restores original signal handlers in the parent.

5.  **Handling Pipes (`handle_pipe_node`):**
    * Creates a pipe using `pipe()` (`create_pipe`).
    * Recursively calls `execute_command` for the left child (`node->data.pipe.left`), setting its `fd_out` to the pipe's write end.
    * Recursively calls `execute_command` for the right child (`node->data.pipe.right`), setting its `fd_in` to the pipe's read end.
    * Carefully closes the correct pipe file descriptors in the parent and children processes to avoid deadlocks or resource leaks.
    * The final output FD returned by the right child becomes the result of `handle_pipe_node`. Waiting for children in pipelines is typically handled higher up in `execute_ast` after the entire pipeline is set up.

6.  **Handling Redirections (`handle_redirection_node`, `process_redirection`, helpers):**
    * **File Opening:** Opens the specified file using `open()` with appropriate flags (`O_RDONLY` for `<`, `O_WRONLY | O_CREAT | O_TRUNC` for `>`, `O_WRONLY | O_CREAT | O_APPEND` for `>>`). Error handling checks for file existence or permissions.
    * **Heredoc (`<<`):** `handle_heredoc` reads input lines using `readline` until the delimiter is found, writing the lines to a pipe. The read end of this pipe is then used as the `fd_in` for the command. It often uses `fork` to handle `readline` separately, allowing `Ctrl+C` to interrupt only the heredoc.
    * **FD Assignment:** The resulting file descriptor from `open` or the heredoc pipe is assigned to the `fd_in` or `fd_out` field of the relevant child command node in the AST.
    * **Applying Redirection:** Before executing the command (in `setup_child_io`), `dup2` is used to connect the command's standard input/output to the file descriptors obtained from the redirection setup.

7.  **Exit Status (`wait_for_children`, `wait_for_processes`, `set_exit_code`):**
    * After commands or pipelines finish, the shell waits for child processes using `waitpid` or `wait`.
    * The termination status of the child is analyzed using macros like `WIFEXITED`, `WEXITSTATUS`, `WIFSIGNALED`, `WTERMSIG`.
    * The `shell->exit_status` is updated accordingly. For pipelines, it's typically the exit status of the *last* command in the sequence.

In essence, the executor walks the AST, setting up the necessary I/O context (pipes, file redirections) and then either executes built-ins directly or forks child processes to execute external commands via `execve`, finally collecting exit statuses.