/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:48:48 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 11:00:11 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file print.h
 * @brief This file contains the function prototypes for printing and error 
 * handling.
 * 
 * This file includes functions for printing strings to file descriptors,
 * handling error messages, and defining error message prefixes for different
 * components of the shell.
 * write() is used for error messages because it is async-signal-safe.
 * This is important when reporting errors from signal handlers, where other I/O
 * functions like printf() would be unsafe to use.
 */

#ifndef PRINT_H
# define PRINT_H

# include "types.h"
# include <unistd.h>
# include <stddef.h>

/* Error message prefixes for different components */
# define PARSER_ERR		"Parser error"
# define AST_ERR		"AST error"
# define EXEC_ERR		"Execution error"
# define SYS_ERR		"System error"
# define READLINE_ERR	"Readline error"
# define REDIR_ERR		"Redirection error"
# define MALLOC_ERR		"Memory allocation error"
# define SYNTAX_ERR		"Syntax error"

void	ft_putstr_fd(const char *s, int fd);
void	ft_error_msg(const char *prefix, const char *msg);

#endif
