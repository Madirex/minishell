## Minishell: extern notes

The `extern` keyword in C has several uses:

### 1. Function declarations:

- Indicates that the function is defined elsewhere, often in another file.
- Allows calling the function before the definition is encountered.

**Example:**

```c
// header.h
extern void print_message(void);

// functions.c
#include <stdio.h>
void print_message(void) {
	printf("Hello, World!\n");
}

// main.c
#include "header.h"

int main(void) {
	print_message();
	return (0);
}
```

### 2. Variable declarations:

- Declares a variable defined in another source file, typically for sharing global variables across files.
- Does not allocate memory; it only declares the existence of the variable.

**Example:**

```c
// globals.c
int shared_variable = 10;

// main.c
#include <stdio.h>
extern int shared_variable;

int main(void) {
	printf("%d\n", shared_variable);
	return (0);
}
```

### **Key points**:

- `extern` does **not allocate memory**; it only declares that a variable or function is defined elsewhere.
- Usually appears in header files to declare functions and global variables accessible from multiple source files.
- Good practice involves explicitly using `extern` for global variables in header files to enhance readability and maintainability.