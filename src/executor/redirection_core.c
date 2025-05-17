/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_core.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:30:27 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/11 18:13:46 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file redirection_core.c
 * @brief Core functions for handling redirections
 * 
 * This file contains the main function for handling different types of
 * redirections in the shell, as well as utility functions for finding
 * redirection nodes in the AST.
 */

#include "minishell.h"
#include "executor/executor.h"

int	process_heredoc_redirection(t_ast_node *node_cpy, t_shell *shell);
int	process_input_redirection(t_ast_node *node_cpy, t_shell *shell);
int	process_output_redirection(t_ast_node *node_cpy, t_shell *shell);

/**
 * @brief Finds an output redirection node in a chain of redirection nodes
 *
 * This function traverses a chain of redirection nodes to find an output
 * or append redirection. If found, it marks the node as processed by setting
 * its type to REDIR_NONE.
 *
 * @param cmd_node The redirection node to start searching from
 * @return A pointer to the found output redirection node, or NULL if none found
 */
t_ast_node	*find_output_redirection_in_chain(t_ast_node *cmd_node)
{
	t_ast_node	*output_redir;

	output_redir = NULL;
	while (cmd_node && cmd_node->type == NODE_REDIRECTION)
	{
		if (cmd_node->data.redirection.type == REDIR_OUTPUT
			|| cmd_node->data.redirection.type == REDIR_APPEND)
		{
			output_redir = cmd_node;
			cmd_node->data.redirection.type = REDIR_NONE;
		}
		cmd_node = cmd_node->data.redirection.child;
	}
	return (output_redir);
}

/**
 * @brief Checks if a node is a command, pipe, or has a redirection child
 *
 * This helper function examines a node to determine its type and updates
 * the provided pointers accordingly.
 *
 * @param cmd The node to check
 * @param cmd_node Pointer to store a command node if found
 * @param pipe_node Pointer to store a pipe node if found
 * @return The next node to check, or NULL if a terminal node was found
 */
t_ast_node	*check_special_node_types(t_ast_node *cmd,
	t_ast_node **cmd_node, t_ast_node **pipe_node)
{
	if (cmd->type == NODE_COMMAND)
	{
		*cmd_node = cmd;
		return (NULL);
	}
	else if (cmd->type == NODE_PIPE)
	{
		*pipe_node = cmd;
		return (NULL);
	}
	else if (cmd->type == NODE_REDIRECTION && cmd->data.redirection.child)
		return (cmd->data.redirection.child);
	return (NULL);
}

/**
 * @brief Selects either a command node or a pipe node as the return value
 *
 * This is a helper function that prioritizes returning a command node over
 * a pipe node when both are present.
 *
 * @param cmd_node The command node to consider
 * @param pipe_node The pipe node to consider
 * @return The command node if not NULL, otherwise the pipe node
 */
t_ast_node	*select_return_node(t_ast_node *cmd_node,
	t_ast_node *pipe_node)
{
	if (cmd_node)
		return (cmd_node);
	return (pipe_node);
}

/**
 * @brief Processes a redirection node based on its type
 *
 * This is the main entry point for handling redirections. It identifies
 * the type of redirection and delegates to the appropriate handler function.
 *
 * @param node_cpy The redirection node to process
 * @param shell The shell environment
 * @return 1 on success, 0 on failure
 */
int	process_redirection(t_ast_node *node_cpy, t_shell *shell)
{
	if (!node_cpy)
		return (0);
	if (node_cpy->data.redirection.type == REDIR_HEREDOC)
		return (process_heredoc_redirection(node_cpy, shell));
	else if (node_cpy->data.redirection.type == REDIR_INPUT)
		return (process_input_redirection(node_cpy, shell));
	else if (node_cpy->data.redirection.type == REDIR_OUTPUT
		|| node_cpy->data.redirection.type == REDIR_APPEND)
		return (process_output_redirection(node_cpy, shell));
	return (0);
}
