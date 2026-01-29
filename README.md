*This project was created as part of the 42 curriculum by kkhachat.*

# Libft

## Description

**Libft** is a foundational project of the 42 curriculum. Its goal is to build a personal C library by reimplementing a set of standard C library functions, as well as additional utility and linked list functions.

The purpose of this project is to:
- Understand how common libc functions work internally
- Practice memory management and pointer manipulation
- Build reusable, well-structured C code
- Create a solid base library to reuse in future 42 projects

The final output of this project is a static library called **`libft.a`**, which can be linked to other C programs.

---

## Instructions

### Requirements

- Language: C  
- Compiler: `cc`  
- Build tools: `make`, `ar`  
- Operating System: Linux or macOS  

All files are compiled with the following flags: `-Wall -Wextra -Werror`

---

### Compilation

To compile the library, run:

```bash
make
```

This will generate the static library **`libft.a`** at the root of the repository.

---

### Makefile Rules

- `make` or `make all`  
  Compiles the library

- `make clean`  
  Removes object files

- `make fclean`  
  Removes object files and **`libft.a`**

- `make re`  
  Rebuilds the library from scratch

---

### Usage

To use the library in another project:

1. Include the header file:

```c
#include "libft.h"
```

2. Compile your program with the library:

```bash
cc main.c -L. -lft
```

Make sure **`libft.a`** is located in the specified library path.

---

## Resources

- Linux man pages  
  (`man strlen`, `man memcpy`, `man malloc`, etc.)

- GNU C Library (glibc) Documentation  
  https://www.gnu.org/software/libc/manual/

- BSD libc Documentation  
  (for `strlcpy`, `strlcat`, and related functions)

- 42 Intranet – Libft Subject PDF

---

## AI Usage

AI tools were used only for documentation support and conceptual clarification (understanding specifications, edge cases, and project requirements).  
No code was generated or copied without manual implementation and full understanding.
