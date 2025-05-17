/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:56:20 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/01/08 11:14:15 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file print_utils.c
 * 
 * The functions in this file are used to print messages and errors to the
 * standard output and standard error streams.
 */

#include "utils/print.h"

/**
 * @brief Formats an error message with prefix and details.
 *
 * This internal helper function combines the prefix and message into a
 * standardized error format. It ensures consistent error message formatting
 * across the shell.
 *
 * @param prefix The error category prefix
 * @param msg The specific error message
 * @param buffer The output buffer to store the formatted message
 * 
 * @note The buffer must be large enough to store the formatted message.
 */
static void	format_error_msg(const char *prefix, const char *msg, char *buffer)
{
	while (*prefix)
		*buffer++ = *prefix++;
	*buffer++ = ':';
	*buffer++ = ' ';
	while (*msg)
		*buffer++ = *msg++;
	*buffer++ = '\n';
	*buffer = '\0';
}

/**
 * @brief Writes a character to the specified file descriptor.
 *
 * Signal-safe function that outputs a single character to the given file
 * descriptor using write().
 *
 * @param c The character to be written
 * @param fd The file descriptor on which to write
 * 
 * @note This function is signal-safe and can be used in signal handlers.
 */
static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/**
 * @brief Writes a string to the specified file descriptor.
 *
 * Signal-safe function for writing strings to a file descriptor.
 * Does not add a newline character at the end of the string.
 *
 * @param s The string to be written
 * @param fd The file descriptor to which the string will be written
 * 
 * @note This function is signal-safe and can be used in signal handlers.
 */
void	ft_putstr_fd(const char *s, int fd)
{
	if (s)
	{
		while (*s)
		{
			ft_putchar_fd(*s, fd);
			s++;
		}
	}
}

/**
 * @brief Formats and outputs an error message with a prefix.
 *
 * Provides standardized error reporting across the shell using a consistent
 * format. Uses only signal-safe operations for output. The message format is:
 * "<prefix>: <msg>\n"
 *
 * @param prefix The error category prefix (use defined constants)
 * @param msg The specific error message
 * 
 * @note This function is signal-safe and can be used in signal handlers.
 */
void	ft_error_msg(const char *prefix, const char *msg)
{
	char	buffer[4096];

	if (!prefix || !msg)
		return ;
	format_error_msg(prefix, msg, buffer);
	ft_putstr_fd(buffer, STDERR_FILENO);
}
