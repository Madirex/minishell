## Minishell: `safe_malloc` and `safe_free`

## `safe_malloc`

### Purpose:
- A custom wrapper function around the standard `malloc` function to ensure safer memory management.

### Functionality:
- Allocates memory dynamically.
- Checks if `malloc` successfully allocated the memory.
- Handles memory allocation failures gracefully.

### Behavior:
- If memory allocation fails (`malloc` returns NULL):
  - Prints a clear and concise error message using `perror` or `strerror`.
  - Exits the program safely (with an appropriate exit status, commonly `EXIT_FAILURE` or a custom-defined error code).

### Benefits:
- Reduces boilerplate code by centralizing memory allocation error handling.
- Simplifies debugging by clearly signaling where allocation failures occur.
- Helps to maintain code readability and consistency.

### Usage example:
```c
void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_error_msg(MALLOC_ERR, "safe_malloc failed");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}
```

---

## `safe_free`

### Purpose:
- A safe wrapper for the standard `free` function to prevent issues like double-free errors and dangling pointers.

### Functionality:
- Checks if the pointer is not NULL before calling `free`.
- Sets the pointer to NULL immediately after freeing it to avoid dangling pointers.

### Behavior:
- If pointer is valid (not NULL):
  - Frees the memory.
  - Resets the pointer to NULL.
- If pointer is NULL:
  - Does nothing, ensuring it's safe to call multiple times.

### Benefits:
- Avoids undefined behavior due to double-free.
- Prevents accidental use of freed memory.
- Simplifies debugging by standardizing memory deallocation.

### Usage example:
```c
void	safe_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
```
Because the argument to `safe_free` is a double pointer, it allows the function to modify the original pointer passed to it, ensuring that the pointer is set to NULL after freeing. The calling code must pass the address of the pointer to `safe_free`, which is why we use `&ptr` in the example: `safe_free((void **)&node->data.command.args);`

---

## Best practices in Minishell context:

- Always use `safe_malloc` instead of direct calls to `malloc`.
- Always pair memory allocations (`safe_malloc`) with deallocations (`safe_free`) to prevent leaks.
- Be cautious when freeing memory in loops or error-handling paths to avoid double-free.
- Regularly test for memory leaks using tools like Valgrind.
