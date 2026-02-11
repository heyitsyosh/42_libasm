#ifndef TESTER_H
# define TESTER_H

# include <stdio.h>	// printf

# define GREEN "\033[32m"
# define RED "\033[31m"
# define GRAY "\033[90m"
# define RESET "\033[0m"

# define PASS_TAG GREEN "[PASS]" RESET
# define FAIL_TAG RED "[FAIL]" RESET

#endif
