## Minishell: header file organization notes

### Unique header names
- Use descriptive and unique header names to avoid conflicts.
- Example:
  - Use `MINISHELL_AST_H` instead of just `AST_H`.

### Include guards
- Always use include guards to prevent multiple inclusions.

### Managing dependencies
- Header dependencies can become complex; handle them carefully.
- Reference guides:
  - [How to manage header file dependencies](https://labex.io/tutorials/c-how-to-manage-header-file-dependencies-419184)
  - [Proper header file etiquette](https://dev.to/pauljlucas/proper-header-file-etiquette-ola)

### Organization and modular structure
- Prefer a modular structure rather than a flat structure.
- Recommended approaches:
  - Have separate headers for each component/module.
  - Consider a hybrid approach:
    - Individual headers per module.
    - One project-wide header (`minishell.h`) to include all individual headers.
    - One types header (`types.h`) for common used types.

### Self-sufficient headers
- A self-sufficient header includes everything required for the associated `.c` file to compile without errors.
- Use forward declarations for structs/unions accessed only by pointers.
- Include full header if a complete struct/union definition is required.
- If several forward declarations are needed, prefer including the header file.

### Order of inclusions
- **Header file (`*.h`) inclusion order**:
  1. Local headers.
  2. System headers (only if necessary and directly used).

- **Source file (`*.c`) inclusion order**:
  1. Corresponding local header.
  2. Other required local headers.
  3. System headers.

### Header directory structure
- Organize headers into subdirectories.
- Avoid using absolute paths; instead, use include paths defined in the build system or makefile.

### System headers inclusion in local headers
- Avoid unless:
  - Directly uses system declarations or definitions.
  - Serves as a wrapper or interface for system functionality.
  - Essential for providing a complete interface.

---

## Project-wide header files

### `minishell.h`
- Main header for the project.
- Includes essential system headers and project-wide type definitions.
- Common declarations and macros.
- Should be included in core files (`main.c`, core utilities, etc.).

#### Typical content
- **Function prototypes**:
  - Command parsing and execution
  - Built-in commands (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`)
  - Signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`)
- **Macro definitions/constants**:
  - Maximum command length, buffer sizes, error codes.
- **Custom type definitions and structs**:
  - Command structure, environment variables.
- **External variable declarations**:
  - Global variables.
- **Utility function prototypes**:
  - `handle_child()`, `handle_pipeline()`, `handle_redirections_pipeline()`, `handle_single_builtin()`

---

### `types.h`
- Defines custom types (structs, enums) used throughout the project.
- Include this directly in `.c` files that explicitly need it.
- Make sure `types.h` is self-sufficient (include other headers or forward declarations as necessary).
