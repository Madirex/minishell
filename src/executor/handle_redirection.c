/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:54:55 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/11 19:24:20 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* @file handle_redirection.c
* @brief Handles redirection operations for the minishell project.
*
* This file contains functions to process input/output redirections,
* heredocs, and command execution with redirection handling.
* It is part of the executor module of the minishell project.
*/

#include "minishell.h"
#include "executor/executor.h"

/**
 * @brief Finds the last output redirection node in a chain of redirections.
 *
 * @param cmd_node The starting node of the redirection chain.
 * @return A pointer to the last output redirection node, or NULL if none 
 * is found.
 */
static t_ast_node	*find_output_redirection_in_chain(t_ast_node *cmd_node)
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
 * @brief Processes a command with output redirection.
 *
 * @param cmd_node The command node to process.
 * @param output_redir The output redirection node.
 * @param fd_in The input file descriptor.
 * @param shell The shell context.
 * @return 1 on success, 0 on failure.
 */
static int	process_cmd_with_output(t_ast_node *cmd_node,
	t_ast_node *output_redir, int fd_in, t_shell *shell)
{
	int	is_pipe;
	int	cmd_fd;
	int	append_flag;
	int	write_result;

	cmd_node->fd_in = fd_in;
	is_pipe = 1;
	cmd_fd = handle_node_command(cmd_node, shell, &is_pipe);
	if (cmd_fd < 0)
		return (1);
	append_flag = (output_redir->data.redirection.type == REDIR_APPEND);
	write_result = ft_write_fd_to_file(cmd_fd,
			output_redir->data.redirection.file, append_flag);
	close(cmd_fd);
	if (write_result == -1)
	{
		shell->exit_status = 1;
		return (0);
	}
	return (1);
}

/**
 * @brief Processes a heredoc redirection.
 *
 * @param node_cpy The redirection node containing the heredoc.
 * @param shell The shell context.
 * @return 1 on success, 0 on failure.
 */
static int	process_heredoc_redirection(t_ast_node *node_cpy, t_shell *shell)
{
	int			heredoc_fd;
	t_ast_node	*cmd_node;
	t_ast_node	*output_redir;

	heredoc_fd = handle_heredoc(node_cpy->data.redirection.file);
	if (heredoc_fd == -1)
		return (0);
	cmd_node = node_cpy->data.redirection.child;
	output_redir = find_output_redirection_in_chain(cmd_node);
	cmd_node = node_cpy->data.redirection.child;
	while (cmd_node && cmd_node->type == NODE_REDIRECTION)
		cmd_node = cmd_node->data.redirection.child;
	if (cmd_node && cmd_node->type == NODE_COMMAND)
	{
		if (output_redir)
			return (process_cmd_with_output(cmd_node, output_redir,
					heredoc_fd, shell));
		cmd_node->fd_in = heredoc_fd;
		return (1);
	}
	close(heredoc_fd);
	return (0);
}

/**
 * @brief Finds the last input redirection node in a chain of redirections.
 *
 * @param node The starting node of the redirection chain.
 * @return A pointer to the last input redirection node.
 */
static t_ast_node	*find_last_input_redirection(t_ast_node *node)
{
	t_ast_node	*last_input;
	t_ast_node	*current;

	last_input = node;
	current = node->data.redirection.child;
	while (current && current->type == NODE_REDIRECTION)
	{
		if (current->data.redirection.type == REDIR_INPUT)
			last_input = current;
		current = current->data.redirection.child;
	}
	return (last_input);
}

/**
 * @brief Closes the file descriptor of a redirection node if needed.
 *
 * @param node The redirection node whose file descriptor may need to be closed.
 */
static void	close_fd_if_needed(t_ast_node *node)
{
	if (node->data.redirection.child->fd_in > 2)
		close(node->data.redirection.child->fd_in);
}
