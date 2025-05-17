/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input_check_pipe.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:56:20 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/20 12:58:59 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_input_check_pipe.c
 * @brief Functions to validate the syntax of pipes in the input string.
 *
 * This file contains functions to check for invalid pipe usage in the input
 * string, including handling quotes and ensuring proper command structure.
 */

#include "minishell.h"

/**
 * @brief Checks if the input starts with a pipe character.
 *
 * @param input The input string to check.
 * @return true if the input starts with a pipe, false otherwise.
 */
static bool	initial_pipe_check(const char *input)
{
	if (input[0] == '|')
		return (true);
	return (false);
}

/**
 * @brief Processes the input string to handle quotes and commands.
 *
 * This function iterates through the input string, updating the state of
 * quotes and checking for valid command structures around pipe characters.
 *
 * @param input The input string to process.
 * @param i Pointer to the current index in the input string.
 * @param found_command Pointer to a boolean indicating if a command was found.
 * @param quote Pointer to the current active quote character, if any.
 * @return true if an invalid pipe structure is detected, false otherwise.
 */
static bool	process_quotes_and_commands(const char *input, int *i,
	bool *found_command, char *quote)
{
	if ((input[*i] == '\'' || input[*i] == '"') && !*quote)
		*quote = input[*i];
	else if (input[*i] == *quote)
		*quote = '\0';
	else if (input[*i] != '|' && !ft_isspace(input[*i]))
		*found_command = true;
	else if (input[*i] == '|' && !*quote)
	{
		if (!*found_command || input[*i + 1] == '|')
			return (true);
		*found_command = false;
	}
	return (false);
}

/**
 * @brief Checks if the input ends with an invalid pipe structure.
 *
 * @param input The input string to check.
 * @param i The current index in the input string.
 * @param found_command Boolean indicating if a command was found.
 * @return true if the input ends with an invalid pipe, false otherwise.
 */
static bool	final_pipe_check(const char *input, int i, bool found_command)
{
	if (!found_command && i > 0 && input[i - 1] == '|')
		return (true);
	return (false);
}

/**
 * @brief Validates the input string for invalid pipe usage.
 *
 * This function checks the input string for invalid pipe usage, including
 * pipes at the beginning or end of the string, consecutive pipes, and pipes
 * within quotes.
 *
 * @param input The input string to validate.
 * @return true if the input contains invalid pipes, false otherwise.
 */
bool	has_invalid_pipes(const char *input)
{
	int		i;
	bool	found_command;
	char	quote;

	i = 0;
	found_command = false;
	quote = '\0';
	if (initial_pipe_check(input))
		return (true);
	while (input[i])
	{
		if (process_quotes_and_commands(input, &i, &found_command, &quote))
			return (true);
		i++;
	}
	if (final_pipe_check(input, i, found_command))
		return (true);
	return (false);
}
