/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validate_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:56:20 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/20 20:04:21 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_validate_input.c
 * @brief Function to validate the input for the parser.
 */

#include "minishell.h"
#include "parser/parser.h"
#include "parser/parser_input_check.h"

/**
 * @brief Validates the input string for the parser.
 * 
 * This function checks for various syntax errors in the input string,
 * including empty input, unclosed quotes, invalid pipes, and invalid
 * redirection syntax.
 * 
 * @param input The input string to validate.
 * @return A syntax error code indicating the type of error found.
 *         Returns SYNTAX_OK if no errors are found.
 * 
 * @note The function uses helper functions to check for specific syntax errors.
 *       - is_empty_or_whitespace: Checks if the input is empty or contains
 *         only whitespace characters.
 *       - has_unclosed_quotes: Checks for unclosed quotes in the input.
 *       - has_invalid_pipes: Checks for invalid pipe syntax.
 *  	 - has_invalid_redirection: Checks for invalid redirection syntax.
 */
t_syntax_error	validate_input(char *input)
{
	if (!input)
		return (SYNTAX_EMPTY);
	if (is_empty_or_whitespace(input))
		return (SYNTAX_EMPTY);
	if (has_unclosed_quotes(input))
		return (SYNTAX_UNCLOSED_QUOTE);
	if (has_invalid_pipes(input))
		return (SYNTAX_MISSING_COMMAND);
	if (has_invalid_redirection(input))
		return (SYNTAX_UNEXPECTED_TOKEN);
	return (SYNTAX_OK);
}
