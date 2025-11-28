<h1 align="center">
	libasm
</h1>

*<p align="center">The aim of this project is to get familiar with assembly language.</p>*

## Description:
Implementation of several C standard library functions in `x86_64 assembly`.  
Some non-standard utility functions are also included.

## Requirements:
This project is written in x86_64 assembly using Intel syntax for NASM compilation.  
Although the code is written for Linux, a macro file is included to support macOS compilation as well.

## Set-up:
First, enter directory with `cd libasm`.
Then use any Makefile command.

#### Makefile Commands:
```Java
make        //compile executable (./so_long)
make test   //
make clean  //delete .o
make fclean //delete .o and executable
make re     //delete .o and executable, recompile 
```

## Usage:  
To use in projects, compile with `-L<path/to/directory/with/libft.a> -lft`.  
Alternatively, compile project files with `path/to/libft.a`.  
Make sure to include `libft.h` appropriately in your source code.
#### Compilation Examples:
```Makefile
gcc main.c -L./libft/ -lft
gcc main.c ./libft/libft.a
```

## Overview:
#### Standard library functions:
| Function | Description |
| ---------- | ----------- |
| [**ft_strlen**](url) | Calculates the length of a string. |
| [**ft_strcpy**](url) | Copies a string from source to destination. |
| [**ft_strcmp**](url) | Compares two strings lexicographically. |
| [**ft_strdup**](url) | Duplicates a string into newly allocated memory. |
| [**ft_read**](url) | Reads data from a file descriptor into a buffer. |
| [**ft_write**](url) | Writes data from a buffer to a file descriptor. |

#### Non-standard utility functions:
| Function | Description |
| ---------- | ----------- |
| [**ft_atoi_base**](url) | Converts a string to an integer in a specified base. |
| [**ft_list_push_front**](url) | Adds an element at the beginning of a list. |
| [**ft_list_size**](url) | Returns the number of nodes in a linked list. |
| [**ft_list_sort**](url) | Sorts list elements from smallest to largest. |
| [**ft_list_remove_if**](url) | Frees and removes list elements for which cmp(data, data_ref) == 0. |
