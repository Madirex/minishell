/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:17:09 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/31 11:39:02 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file handle_quotes_utils.c
 * @brief Utility functions for handling quotes and escape sequences.
 * 
 * This file contains functions to process escape sequences within quotes,
 * toggle active quotes, and check if a character is a quote. It is part of
 * a larger program that handles string processing, particularly in the context
 * of shell commands or similar applications.
 */

#include "utils/str_utils.h"

bool	process_escape_outside_quotes(t_escape_params *params);

/**
 * @brief Processes escape sequences within quotes.
 * 
 * @param params The parameters for processing escape sequences.
 * @return true if an escape sequence was processed, false otherwise.
 * 
 * This function handles escape sequences within quotes. It checks if the next
 * character is a quote and processes it accordingly. If the next character is
 * a double quote, it adds a double quote to the result. If it's a single
 * quote, it adds a backslash and a single quote to the result. The function
 * updates the indices accordingly.
 */
bool	process_escape(t_escape_params *params)
{
	if (params->str[*(params->i)] != '\\')
		return (false);
	if (params->active_quote == '"')
		return (process_escape_in_quotes(params));
	if (params->active_quote == '\0')
		return (process_escape_outside_quotes(params));
	params->result[*(params->j)] = params->str[*(params->i)];
	(*(params->j))++;
	(*(params->i))++;
	return (true);
}

/**
 * @brief Checks if a character is a quote.
 * 
 * @param c The character to check.
 */
bool	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (true);
	return (false);
}

/**
 * @brief Toggles the active quote character.
 * 
 * @param c The character to toggle.
 * @param active_quote Pointer to the active quote character.
 * 
 * This function checks if the active quote is empty. If it is, it sets the
 * active quote to the given character. If the character matches the active
 * quote, it resets the active quote to empty. This is used to track whether
 * we are currently inside a quote or not.
 */
void	toggle_active_quote(char c, char *active_quote)
{
	if (*active_quote == '\0')
		*active_quote = c;
	else if (c == *active_quote)
		*active_quote = '\0';
}

/**
 * @brief Processes escape sequences within quotes.
 * 
 * @param params The parameters for processing escape sequences.
 * @return true if an escape sequence was processed, false otherwise.
 */
bool	process_escape_in_quotes(t_escape_params *params)
{
	if (params->str[*(params->i) + 1] == '"')
	{
		params->result[*(params->j)] = '"';
		(*(params->j))++;
		(*(params->i)) += 2;
		return (true);
	}
	if (params->str[*(params->i) + 1] == '\'')
	{
		params->result[*(params->j)] = '\\';
		(*(params->j))++;
		params->result[*(params->j)] = '\'';
		(*(params->j))++;
		(*(params->i)) += 2;
		return (true);
	}
	return (false);
}
