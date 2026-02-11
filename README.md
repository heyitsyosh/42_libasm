<h1 align="center">
	libasm
</h1>

*<p align="center">The aim of this project is to get familiar with assembly language.</p>*

## Description:
Implementation of several C standard library functions in `x86_64 assembly`.  
Some non-standard utility functions are also included.

## Requirements:
This project targets **Linux on x86_64**.  
All assembly code is written in **Intel syntax** and assembled with **NASM**.

## Set-up:
First, enter directory with `cd libasm`.  
Then use any Makefile command.

#### Makefile Commands:
```Java
make        //compile library (to libasm.a)
make test   //compile test
make clean  //delete .o
make fclean //delete .o and .a
make re     //delete .o and .a and recompile library
```

## Usage:  
To use in projects, compile with `-L<path/to/directory/with/libasm.a> -lasm`.  
Alternatively, compile project files with `path/to/libasm.a`.  
#### Compilation Examples:
```Makefile
gcc main.c -L./libasm -lasm
gcc main.c ./libasm/libasm.a
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
