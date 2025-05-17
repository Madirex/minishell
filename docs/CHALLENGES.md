
## Minishell: main challenges

### 1. Signal handling with constraints
Managing `Ctrl-C`, `Ctrl-D`, and `Ctrl-\` while only using a single global variable posed a significant design challenge. Mimicking bash behavior in interactive mode forced a deeper understanding of signal mechanics and user experience expectations.

### 2. Complex quote and variable expansion
Parsing input with nested or mixed quotes, and dealing with ambiguous redirection scenarios due to unquoted variables (`> $AMB_TEST` vs `> "$AMB_TEST"`) revealed the intricacies of shell parsing.

### 3. Redirection and pipe management
Ensuring that all file descriptors were properly managed during piped and redirected execution chains (e.g., `cat | cat | ls`) required precision. Here-doc support and edge case handling added further complexity.

### 4. Process and environment isolation
Understanding that child processes (e.g., commands in a pipe) shouldn’t alter the parent’s environment (like with `export`) was a critical insight. Cases with missing variables like `PATH` or `OLDPWD` pushed the shell’s robustness.

### 5. Compliance and memory management
Following the strict Norm guidelines while maintaining leak-free memory usage required consistent discipline. Debugging subtle leaks or style violations became part of the routine.

### 6. Built-in command edge cases
Reproducing bash quirks in built-ins (like `echo -nnnnnnnA`) demanded testing and fine-tuned parsing logic.

### 7. Scope management and bash fidelity
Determining what behavior to replicate from bash and what to exclude, without introducing errors, sharpened decision-making and reinforced clear project boundaries.