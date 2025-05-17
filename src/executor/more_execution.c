/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:53:26 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/15 18:38:28 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file more_execution.c
 * @brief Functions for executing the "more" command
 * 
 * This file contains functions for executing the "more" command,
 * which is used to display text files one screen at a time.
 * It includes functions for initializing the "more" process,
 * sending data to it, and handling errors.
 */

#include "minishell.h"

bool	init_more_process(t_more_data *data);
bool	send_data_to_more(int fd, char *buffer,
			size_t size, t_more_data *data);

/**
 * @brief More execution.
 *
 * This function executes more.
 *
 * @param fd File descriptor.
 * @param buffer Buffer.
 * @param buffer_size Buffer size.
 *
 * @return True if more was executed correctly, false if it failed.
 */
bool	more_execution(int fd, char *buffer, size_t buffer_size)
{
	t_more_data	data;

	if (!init_more_process(&data))
	{
		close(data.pipe_fd[0]);
		close(data.pipe_fd[1]);
		return (false);
	}
	close(data.pipe_fd[0]);
	return (send_data_to_more(fd, buffer, buffer_size, &data));
}

/**
 * @brief Find command node inside redirection chain
 *
 * @param redir The redirection node to start from
 * @return The command node or NULL if not found
 */
static t_ast_node	*find_cmd_in_redir(t_ast_node *redir)
{
	t_ast_node	*last_cmd;

	last_cmd = NULL;
	while (redir && redir->type == NODE_REDIRECTION)
	{
		if (redir->data.redirection.child
			&& redir->data.redirection.child->type == NODE_COMMAND)
		{
			last_cmd = redir->data.redirection.child;
			break ;
		}
		redir = redir->data.redirection.child;
	}
	return (last_cmd);
}

/**
 * @brief Find the last command node in a pipe chain
 *
 * @param node The AST node to start from
 * @return The last command node or NULL if not found
 */
static t_ast_node	*find_last_command_node(t_ast_node *node)
{
	t_ast_node	*last_cmd;
	t_ast_node	*right_node;

	if (!node)
		return (NULL);
	last_cmd = NULL;
	if (node->type == NODE_PIPE)
	{
		while (node && node->type == NODE_PIPE)
		{
			if (node->data.pipe.right)
			{
				right_node = node->data.pipe.right;
				if (right_node->type == NODE_COMMAND)
					last_cmd = right_node;
				else if (right_node->type == NODE_REDIRECTION)
					last_cmd = find_cmd_in_redir(right_node);
			}
			node = node->data.pipe.right;
		}
	}
	else if (node->type == NODE_COMMAND)
		last_cmd = node;
	return (last_cmd);
}

/**
 * @brief Check if the last command in a pipe chain is "more"
 *
 * @param node The AST node to check
 * @return true if the last command is "more", false otherwise
 */
bool	is_more_last_command(t_ast_node *node)
{
	t_ast_node	*last_cmd;
	char		*cmd_name;

	last_cmd = find_last_command_node(node);
	if (last_cmd && last_cmd->type == NODE_COMMAND)
	{
		cmd_name = last_cmd->data.command.name;
		if (cmd_name && (ft_strcmp(cmd_name, "more") == 0
				|| ft_strcmp(cmd_name, "less") == 0))
			return (true);
	}
	return (false);
}
