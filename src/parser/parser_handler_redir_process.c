/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler_redir_process.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:55:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/13 20:13:02 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_handler_redir_process.c
 * @brief Helper functions for processing redirection arguments.
 */

#include "parser/parser.h"

/**
 * @brief Updates the command arguments in the command node.
 * 
 * @param state Parser state.
 * @param cmd_node Command node to update.
 * @return true if update was successful, false otherwise.
 * 
 * This function prepares the command arguments by counting the number of
 * valid arguments and allocating memory for them.
 * It also copies the valid tokens into the command arguments array.
 * 
 * @note This function assumes that the command node is already initialized
 * and valid.
 */
static bool	update_command_args(t_parser_state *state, t_ast_node *cmd_node)
{
	int		count;
	char	**new_args;

	count = count_cmd_args(cmd_node);
	new_args = prepare_additional_args(state, cmd_node, count);
	if (!new_args)
		return (false);
	free_array(cmd_node->data.command.args);
	cmd_node->data.command.args = new_args;
	state->index += count;
	return (true);
}

/**
 * @brief Processes additional arguments after a redirection.
 * 
 * @param state Parser state.
 * @param redir_node Redirection node being processed.
 * @return true if processing was successful, false otherwise.
 */
bool	process_redir_arguments(t_parser_state *state, t_ast_node *redir_node)
{
	t_ast_node	*cmd_node;

	if (!state->tokens[state->index]
		|| is_redirection_token(state->tokens[state->index])
		|| is_pipe_token(state->tokens[state->index]))
		return (false);
	cmd_node = state->last_command_node;
	if (!cmd_node || cmd_node->type != NODE_COMMAND)
		return (false);
	if (!update_command_args(state, cmd_node))
	{
		attach_redir_to_ast(state, redir_node);
		return (false);
	}
	return (true);
}
