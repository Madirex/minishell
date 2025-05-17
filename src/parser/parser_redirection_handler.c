/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection_handler.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:45:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/13 20:13:54 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_redirection_handler.c
 * @brief Functions for handling redirections in the parser.
 */

#include "parser/parser.h"

/**
 * @brief Checks if redirection is valid.
 * 
 * @param state Parser state.
 * @return true if valid, false otherwise.
 */
bool	is_redirection_valid(t_parser_state *state)
{
	if (state->tokens[state->index + 1] == NULL)
	{
		ft_error_msg(PARSER_ERR,
			"Syntax error: Missing file for redirection");
		state->ast->syntax_error = SYNTAX_UNEXPECTED_TOKEN;
		return (false);
	}
	return (true);
}

/**
 * @brief Creates a redirection node for a pipe.
 * 
 * @param state Parser state.
 * @param right_node Command node for redirection.
 * @return New redirection node or NULL on error.
 */
t_ast_node	*create_pipe_redirection(t_parser_state *state,
	t_ast_node *right_node)
{
	t_ast_node	*redir_node;

	if (!is_redirection_valid(state))
		return (NULL);
	redir_node = create_redir_node(
			get_redirection_type(state->tokens[state->index]),
			ft_strdup(state->tokens[state->index + 1]),
			right_node);
	if (!redir_node)
	{
		ft_error_msg(PARSER_ERR, "Memory allocation error in handle_pipe");
		state->ast->syntax_error = SYNTAX_UNEXPECTED_TOKEN;
		return (NULL);
	}
	state->index += 2;
	return (redir_node);
}

/**
 * @brief Process redirections for a pipe command.
 * 
 * @param state Parser state.
 * @param right_node Command node to process redirections for.
 * @return Updated node after redirections processing.
 */
t_ast_node	*process_pipe_redirections(t_parser_state *state,
	t_ast_node *right_node)
{
	t_ast_node	*redir_node;

	while (state->tokens[state->index]
		&& is_redirection_token(state->tokens[state->index]))
	{
		redir_node = create_pipe_redirection(state, right_node);
		if (!redir_node)
			return (NULL);
		right_node = process_additional_args(state, right_node);
		if (!right_node)
			return (NULL);
		right_node = redir_node;
	}
	return (right_node);
}
