# Minishell notes: dynamic buffering in C

Dynamic buffering refers to allocating and resizing memory at runtime rather than relying on fixed-size arrays. It provides flexibility when dealing with data whose size is not known in advance.

## Why use dynamic buffers?

Static buffers, such as `char buffer[1024];`, are limited:
- They can waste memory if oversized.
- They may lead to buffer overflows if undersized.

Dynamic buffers solve this by growing or shrinking as needed, making them ideal for:
- Reading user input of unknown size
- Parsing commands or tokens
- Processing data from streams or pipes
- Managing dynamically generated content like logs or error messages

## How to implement dynamic buffers

A basic implementation involves:

```c
char    *buffer;
size_t  capacity;
size_t  length;
```

### Step-by-step

1. **Initialize** the buffer:

```c
capacity = 64;
length = 0;
buffer = malloc(capacity);
if (!buffer)
    return (NULL);
```

2. **Append data** while expanding the buffer if needed:

```c
if (length + new_data_len >= capacity)
{
    capacity *= 2;
    buffer = realloc(buffer, capacity);
    if (!buffer)
        return (NULL);
}
memcpy(buffer + length, new_data, new_data_len);
length += new_data_len;
```

3. **Null-terminate** the buffer (if treating as a string):

```c
buffer[length] = '\0';
```

4. **Free** the buffer when done:

```c
free(buffer);
```

## Practical tips

- Always check for `NULL` after `malloc` or `realloc`.
- Use exponential growth (e.g., double the size) to avoid frequent reallocations.
- Don't forget to null-terminate if you're building a string.
- Initialize `length` and `capacity` clearly to avoid logic bugs.

## Applications in Minishell

In the `minishell` project, dynamic buffering is especially useful for:
- Reading and parsing user input
- Handling here-documents
- Accumulating command tokens
- Managing expandable strings or logs

Using dynamic buffers helps create more robust and adaptable software by avoiding assumptions about input size or structure.
