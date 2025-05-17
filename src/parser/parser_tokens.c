/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:00:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/20 20:02:52 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * * @file parser_tokens.c
 * 
 * * This file contains functions to check the type of tokens used in a shell
 * * parser. It includes functions to identify command groups, pipe tokens,
 * * redirection tokens, operator tokens, and argument tokens.
 */

#include "parser/parser_tokens.h"

/**
 * @brief Checks if the given token is a command group.
 *
 * This function determines whether the provided token represents 
 * a command group.
 *
 * @param token The token to be checked.
 * @return true if the token is a command group, false otherwise.
 * 
 * @note A command group is represented by parentheses.
 */
bool	is_command_group(const char *token)
{
	if (token && token[0] == '(')
		return (true);
	return (false);
}

/**
 * @brief Checks if the given token is a pipe token.
 *
 * This function compares the provided token with the pipe character "|".
 * If the token matches, it returns true. Otherwise, it returns false.
 *
 * @param token The token to be checked.
 * @return true if the token is a pipe token, false otherwise.
 */
bool	is_pipe_token(const char *token)
{
	if (token && ft_strcmp(token, "|") == 0)
		return (true);
	return (false);
}

/**
 * @brief Checks if the given token is a redirection token.
 *
 * This function determines whether the provided token is a redirection token
 * (e.g., '>', '>>', '<', '<<') used in shell commands.
 *
 * @param token The token to be checked.
 * @return true if the token is a redirection token, false otherwise.
 */
bool	is_redirection_token(const char *token)
{
	if (!token)
		return (false);
	if (ft_strcmp(token, ">") == 0)
		return (true);
	if (ft_strcmp(token, "<") == 0)
		return (true);
	if (ft_strcmp(token, ">>") == 0)
		return (true);
	if (ft_strcmp(token, "<<") == 0)
		return (true);
	return (false);
}

/**
 * @brief Checks if the given token is an operator.
 *
 * This function determines whether the provided token is an operator token.
 *
 * @param token The token to be checked.
 * @return true if the token is an operator, false otherwise.
 */
bool	is_operator_token(const char *token)
{
	if (is_pipe_token(token))
		return (true);
	if (is_redirection_token(token))
		return (true);
	return (false);
}

/**
 * @brief Checks if the given token is an argument token.
 *
 * This function determines whether the provided token is an argument token
 * based on the last node in the parser state.
 *
 * @param token The token to be checked.
 * @param state The parser state containing the last node.
 * @return true if the token is an argument token, false otherwise.
 */
bool	is_argument_token(const char *token, t_parser_state *state)
{
	t_ast_node	*current_node;

	if (!token)
		return (false);
	if (!state)
		return (false);
	if (is_operator_token(token))
		return (false);
	current_node = state->last_node;
	while (current_node && current_node->type == NODE_REDIRECTION)
		current_node = current_node->data.redirection.child;
	if (current_node && current_node->type == NODE_COMMAND)
		return (true);
	return (false);
}
