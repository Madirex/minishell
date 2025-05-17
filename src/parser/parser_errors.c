/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:00:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/14 10:09:10 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_errors.c
 * @brief Functions for reporting parser syntax errors.
 * 
 * This file contains functions for reporting syntax errors that occur during
 * the parsing of shell commands.
 */

#include "parser/parser_errors.h"
#include "utils/print.h"

/**
 * @brief Reports parser syntax errors using standardized error reporting.
 *
 * Uses the centralized error reporting mechanism to output syntax errors
 * with the PARSER_ERR prefix. All messages are signal-safe and follow
 * the shell's standardized error format.
 *
 * @param error The type of syntax error that occurred
 * @return void
 * 
 * @note This function does not return a value. It reports the error directly.
 */
static const char	*get_error_message(t_syntax_error error)
{
	static const char	*messages[] = {
	[SYNTAX_OK] = NULL,
	[SYNTAX_EMPTY] = "syntax error: empty command",
	[SYNTAX_UNEXPECTED_TOKEN] = "syntax error near unexpected token `%s'",
	[SYNTAX_MISSING_OPERATOR] = "syntax error: missing operator",
	[SYNTAX_MISSING_COMMAND] = "syntax error near unexpected token `%s'",
	[SYNTAX_UNCLOSED_QUOTE] = "syntax error: unclosed quote",
	[SYNTAX_UNCLOSED_SUBSHELL] = "syntax error: unclosed subshell",
	[SYNTAX_COMMAND_NOT_FOUND] = "%s"
	};

	return (messages[error]);
}

/**
 * @brief Returns the token to be displayed in error messages.
 *
 * This function returns the token that caused the syntax error. If the token
 * is NULL or empty, it returns a default token based on the error type.
 *
 * @param error The type of syntax error that occurred
 * @param token The token that caused the error
 * 
 * @return The token to be displayed in error messages
 */
static const char	*get_display_token(t_syntax_error error, const char *token)
{
	if (!token || !*token)
	{
		if (error == SYNTAX_MISSING_COMMAND)
			return ("|");
		return ("newline");
	}
	return (token);
}

/**
 * @brief Format a string with a single token replacement
 * 
 * Safely formats a message by replacing %s with the token.
 * 
 * @param dest Destination buffer
 * @param dest_size Size of destination buffer
 * @param format Format string
 * @param token Token to insert
 */
static void	safe_format(char *dest, size_t dest_size, const char *format,
	const char *token)
{
	size_t	i;
	size_t	len;
	size_t	j;

	i = 0;
	len = 0;
	while (format[i] && len < dest_size - 1)
	{
		if (format[i] == '%' && format[i + 1] == 's')
		{
			j = 0;
			while (token[j] && len < dest_size - 1)
				dest[len++] = token[j++];
			i += 2;
		}
		else
			dest[len++] = format[i++];
	}
	dest[len] = '\0';
}

void	get_syntax_error_message(t_syntax_error error, const char *token)
{
	char		error_msg[256];
	const char	*message;
	const char	*display_token;

	if (error == SYNTAX_OK)
		return ;
	message = get_error_message(error);
	if (!message)
		return ;
	if (error == SYNTAX_UNEXPECTED_TOKEN || error == SYNTAX_MISSING_COMMAND
		|| error == SYNTAX_COMMAND_NOT_FOUND)
	{
		display_token = get_display_token(error, token);
		safe_format(error_msg, sizeof(error_msg), message, display_token);
		if (error == SYNTAX_COMMAND_NOT_FOUND)
			ft_error_msg("", error_msg);
		else
			ft_error_msg(PARSER_ERR, error_msg);
		return ;
	}
	ft_error_msg(PARSER_ERR, message);
}

/**
 * @brief Handles parser syntax errors by reporting them to the user.
 * 
 * This function checks if a syntax error occurred during parsing and
 * reports it to the user using the get_syntax_error_message function.
 * It also sets the shell's exit status to 2, which is the standard exit 
 * code for syntax errors in bash.
 * 
 * @param error The type of syntax error that occurred
 * @param shell Pointer to the shell structure to update exit status
 * @return void
 * 
 * @note This function does not return a value. It reports the error directly.
 */
void	handle_error(t_syntax_error error, t_shell *shell, const char *token)
{
	if (error != SYNTAX_OK)
	{
		get_syntax_error_message(error, token);
		if (shell)
			shell->exit_status = 2;
		return ;
	}
}
