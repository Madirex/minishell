## Minishell: `volatile` notes

The `volatile` keyword tells the compiler that a variable's value can change unexpectedly, often due to external factors like hardware operations or concurrent access in multithreaded programs.

```c
volatile int timer_counter;
```

Key points:

- Prevents the compiler from optimizing accesses to volatile variables.
- Ensures that every read/write operation on the variable actually occurs.
- Commonly used for memory-mapped I/O registers, shared variables in multithreading, and interrupt service routines.

Best practice:
Use `volatile` sparingly, as it can impact performance. Only use it when necessary to ensure correctness in situations where unexpected changes might occur.