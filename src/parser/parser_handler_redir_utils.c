/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler_redir_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:32:06 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/13 20:13:34 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * * @file parser_handler_redir_utils.c
 * 
 * * @brief Utility functions for handling redirection in the parser.
 * 
 * * This file contains utility functions for handling redirection in the
 * * parser state. It includes functions for validating redirection syntax,
 * * preparing redirection nodes, and managing command arguments.
 */
#include "parser/parser.h"

/**
 * @brief Handles the redirection in the parser state.
 *
 * This function processes the redirection operator found at the specified
 * position in the parser state. It updates the parser state accordingly
 * to handle the redirection.
 *
 * @param state Pointer to the parser state structure.
 * @param redir_pos Position of the redirection operator in the input.
 * 
 * @note The redirection operator is expected to be at the specified position.
 */
bool	validate_redirection(t_parser_state *state, int redir_pos)
{
	if (!state || !state->tokens || !state->tokens[redir_pos])
	{
		ft_error_msg(PARSER_ERR, "Invalid state or NULL token");
		return (false);
	}
	if (!state->tokens[redir_pos + 1])
	{
		ft_error_msg(PARSER_ERR, "Syntax error: Missing file for redirection");
		return (false);
	}
	if (is_redirection_token(state->tokens[redir_pos + 1])
		|| is_pipe_token(state->tokens[redir_pos + 1])
		|| is_command_group(state->tokens[redir_pos + 1]))
	{
		ft_error_msg(PARSER_ERR,
			"Syntax error: Invalid file name for redirection");
		return (false);
	}
	if (!state->last_command_node)
	{
		ft_error_msg(PARSER_ERR, "Syntax error: Redirection without a command");
		return (false);
	}
	return (true);
}

/**
 * @brief Prepares a redirection node for the AST.
 * 
 * This function prepares a redirection node for the abstract syntax tree (AST)
 * using the given redirection type and filename. It creates a new redirection
 * node and sets its type, file, and child command node.
 * 
 * @param state Pointer to the parser state structure.
 * @param redir_pos Position of the redirection operator in the input.
 * @return A pointer to the created redirection node.
 * 
 */
t_ast_node	*prepare_redir_node(t_parser_state *state, int redir_pos)
{
	t_redir_type	redir_type;
	char			*filename;
	t_ast_node		*redir_node;

	redir_type = get_redirection_type(state->tokens[redir_pos]);
	if (redir_type == REDIR_NONE)
		return (NULL);
	filename = ft_strdup(state->tokens[redir_pos + 1]);
	if (!filename)
	{
		ft_error_msg(PARSER_ERR,
			"Error: Memory allocation failed for filename");
		return (NULL);
	}
	redir_node = create_redir_node(redir_type, filename,
			state->last_command_node);
	if (!redir_node)
	{
		safe_free((void **)&filename);
		return (NULL);
	}
	return (redir_node);
}
