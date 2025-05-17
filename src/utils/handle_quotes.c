/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:55:08 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/31 14:35:47 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file handle_quotes.c
 * @brief Functions for handling quotes and escape sequences.
 * 
 * This file contains functions to process escape sequences within quotes,
 * toggle active quotes, and check if a character is a quote. It is part of
 * a larger program that handles string processing, particularly in the context
 * of shell commands or similar applications.
 */

#include "utils/str_utils.h"

void	*safe_malloc(size_t size);
bool	is_quote(char c);
void	toggle_active_quote(char c, char *active_quote);
bool	process_escape_in_quotes(t_escape_params *params);
bool	process_escape(t_escape_params *params);
bool	process_escape_outside_quotes(t_escape_params *params);

/**
 * @brief Initializes the parameters for processing quotes.
 * 
 * @param arg The input string to process.
 * @param result The result string to store the processed output.
 * @param params The structure to hold the parameters for processing.
 * @param indices Structure containing i and j indices
 * 
 * This function initializes the parameters for processing quotes and escape
 * sequences. It sets the active quote to '\0', assigns the input string
 * to the str field, and initializes the indices for processing. The result
 * string is also assigned to the result field.
 */
static void	initialize_params(
	char *arg,
	char *result,
	t_escape_params *params,
	t_indices *indices)
{
	params->active_quote = '\0';
	params->str = arg;
	params->i = &indices->i;
	params->result = result;
	params->j = &indices->j;
}

/**
 * @brief Processes escape sequences in quotes.
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
bool	process_escape_outside_quotes(t_escape_params *params)
{
	if (params->str[*(params->i) + 1] == '"'
		|| params->str[*(params->i) + 1] == '\'')
	{
		params->result[*(params->j)] = params->str[*(params->i) + 1];
		(*(params->j))++;
		(*(params->i)) += 2;
		return (true);
	}
	return (false);
}

/**
 * @brief Initialize result string and indices for quote handling
 * 
 * @param arg Input string
 * @param result Pointer to result string
 * @param indices Pointer to indices structure
 * @return true if initialization successful, false otherwise
 * 
 * This function allocates memory for the result string and initializes
 * the indices for processing quotes. It checks if the input string is
 * valid and allocates memory accordingly. The result string is
 * initialized to the same length as the input string, and the indices
 * are set to zero.
 * 
 * @note The caller is responsible for freeing the allocated memory.
 */
static bool	init_quote_handling(char *arg, char **result, t_indices *indices)
{
	int	len;

	if (!arg)
		return (false);
	len = ft_strlen(arg);
	*result = safe_malloc(len + 1);
	if (!*result)
		return (false);
	indices->i = 0;
	indices->j = 0;
	return (true);
}

/**
 * @brief Process a character in the quote handling loop
 * 
 * @param arg Input string
 * @param result Result string
 * @param indices Pointer to indices structure
 * @param params Escape parameters
 * 
 * This function processes a single character in the input string
 * based on the current state of quotes and escape sequences. It checks
 * if the character is a quote or an escape sequence and updates the
 * result string and indices accordingly. If the character is a quote,
 * it toggles the active quote state. If it's an escape sequence, it
 * processes it based on the current active quote. The function
 * handles both single and double quotes, as well as escape sequences.
 */
static void	process_character(char *arg, char *result, t_indices *indices,
	t_escape_params *params)
{
	if (params->active_quote == '\'')
	{
		if (arg[indices->i] == '\'')
		{
			toggle_active_quote(arg[indices->i], &params->active_quote);
			indices->i++;
			return ;
		}
		result[indices->j++] = arg[indices->i++];
		return ;
	}
	if (process_escape(params))
		return ;
	if (is_quote(arg[indices->i]))
	{
		toggle_active_quote(arg[indices->i], &params->active_quote);
		indices->i++;
		return ;
	}
	result[indices->j++] = arg[indices->i++];
}

/**
 * @brief Handle quotes in a string
 * 
 * @param arg Input string
 * @return Processed string with quotes handled
 * 
 * This function processes a string to handle quotes and escape sequences.
 * It initializes the necessary parameters, processes each character in
 * the input string, and returns the processed result. The function
 * allocates memory for the result string and ensures that it is properly
 * terminated. The caller is responsible for freeing the allocated memory.
 */
char	*handle_quotes(char *arg)
{
	char			*result;
	t_indices		indices;
	t_escape_params	params;

	if (!init_quote_handling(arg, &result, &indices))
		return (NULL);
	initialize_params(arg, result, &params, &indices);
	while (arg[indices.i])
	{
		if ((params.active_quote == '"' && arg[indices.i] == '\'')
			|| (params.active_quote == '\'' && arg[indices.i] == '"'))
		{
			result[indices.j++] = arg[indices.i++];
		}
		else
			process_character(arg, result, &indices, &params);
	}
	result[indices.j] = '\0';
	return (result);
}
