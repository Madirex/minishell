/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:56:20 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/20 20:02:39 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_input_check.c
 * @brief Functions to validate and check the input for the parser.
 *
 * This file contains utility functions to check for invalid redirections,
 * unclosed quotes, and empty or whitespace-only inputs in the shell parser.
 */

#include "minishell.h"

/**
 * @brief Checks if the input contains invalid redirections.
 *
 * This function scans the input string to detect invalid redirection syntax,
 * such as consecutive redirection operators or missing target tokens.
 *
 * @param input The input string to check.
 * @return true if invalid redirection is found, false otherwise.
 */
bool	has_invalid_redirection(const char *input)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '"') && !quote)
			quote = input[i];
		else if (input[i] == quote)
			quote = '\0';
		else if ((input[i] == '>' || input[i] == '<') && !quote)
		{
			i++;
			if (input[i] == input[i - 1])
				i++;
			while (ft_isspace(input[i]))
				i++;
			if (!input[i] || input[i] == '>' || input[i] == '<'
				|| input[i] == '|')
				return (true);
		}
		i++;
	}
	return (false);
}

/**
 * @brief Checks if the input contains unclosed quotes.
 *
 * This function scans the input string to detect if there are any unclosed
 * single or double quotes.
 *
 * @param input The input string to check.
 * @return true if unclosed quotes are found, false otherwise.
 */
bool	has_unclosed_quotes(const char *input)
{
	char	quote_char;
	int		i;
	bool	in_quote;

	in_quote = false;
	i = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '"'))
		{
			if (!in_quote)
			{
				quote_char = input[i];
				in_quote = true;
			}
			else if (input[i] == quote_char)
				in_quote = false;
		}
		i++;
	}
	return (in_quote);
}

/**
 * @brief Checks if the input is empty or contains only whitespace.
 *
 * This function scans the input string to determine if it is empty or
 * consists solely of whitespace characters.
 *
 * @param input The input string to check.
 * @return true if the input is empty or whitespace-only, false otherwise.
 */
bool	is_empty_or_whitespace(const char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (false);
		i++;
	}
	return (true);
}
