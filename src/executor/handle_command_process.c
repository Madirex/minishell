/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:45:36 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/11 19:21:38 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor/executor.h"

int			process_redirection(t_ast_node *node_cpy, t_shell *shell);
int			handle_node_command(t_ast_node *node_cpy, t_shell *shell,
				int *is_pipe);

/**
 * @brief Handle heredoc input redirection and update last input file descriptor
 * 
 * @param current The current redirection node
 * @param shell The shell struct
 * @param last_input_fd Pointer to store last input file descriptor
 * 
 * @return 1 on success, 0 on failure
 */
static int	handle_heredoc_input(t_ast_node *current,
			t_shell *shell, int *last_input_fd)
{
	if (!process_redirection(current, shell))
		return (0);
	if (current->fd_in > 2)
		*last_input_fd = current->fd_in;
	else if (current->data.redirection.child
		&& current->data.redirection.child->fd_in > 2)
		*last_input_fd = current->data.redirection.child->fd_in;
	return (1);
}

/**
 * @brief Process redirection nodes in sequence
 * 
 * @param current initial redirection node
 * @param shell the shell struct
 * @param last_input_fd pointer to store last input fd
 * @param last_output pointer to store last output node
 * 
 * @return command node if found, NULL otherwise
 */
static t_ast_node	*process_redirection_nodes(t_ast_node *current,
				t_shell *shell, int *last_input_fd, t_ast_node **last_output)
{
	t_ast_node	*cmd_node;

	cmd_node = NULL;
	while (current && current->type == NODE_REDIRECTION)
	{
		if (current->data.redirection.type == REDIR_OUTPUT
			|| current->data.redirection.type == REDIR_APPEND)
			handle_output_redirection(current, last_output);
		else if (current->data.redirection.type == REDIR_INPUT)
		{
			if (!handle_input_redirection(current, shell, last_input_fd))
				return (NULL);
		}
		else if (current->data.redirection.type == REDIR_HEREDOC)
		{
			if (!handle_heredoc_input(current, shell, last_input_fd))
				return (NULL);
		}
		cmd_node = find_cmd_node(current);
		if (cmd_node)
			return (cmd_node);
		current = current->data.redirection.child;
	}
	return (NULL);
}

/** 
 * @brief Process redirection
 *
 * @param node the node
 * @param shell the shell struct
 * 
 * @return the file descriptor or -1 on failure
 */
static int	process_redirections(t_ast_node *node, t_shell *shell)
{
	int			last_input_fd;
	t_ast_node	*cmd_node;
	t_ast_node	*last_output;
	int			cmd_result;

	last_input_fd = -1;
	last_output = NULL;
	cmd_node = process_redirection_nodes(node, shell,
			&last_input_fd, &last_output);
	if (!cmd_node)
		return (-1);
	cmd_result = execute_cmd_with_redirections(cmd_node, last_output,
			last_input_fd, shell);
	if (cmd_result > 0 && cmd_node->fd_in > 2)
		return (cmd_node->fd_in);
	return (cmd_result);
}

/**
 * @brief Handle command node
 *
 * @param node the node
 * @param shell the shell struct
 * @param is_pipe if the command is a pipe
 *
 * @return the fd of the out
 */
int	handle_command_node(t_ast_node *node, t_shell *shell, int is_pipe)
{
	int	cmd_fd;

	cmd_fd = handle_node_command(node, shell, &is_pipe);
	if (cmd_fd >= 0)
		node->fd_in = cmd_fd;
	if (node->fd_in != STDIN_FILENO)
		return (node->fd_in);
	return (-1);
}

/**
 * @brief Handle redirection node
 *
 * @param node the node
 * @param shell the shell struct
 *
 * @return the fd of the out
 */
int	handle_redirection_node(t_ast_node *node, t_shell *shell)
{
	int	result;

	if (node->data.redirection.child
		&& node->data.redirection.child->type == NODE_PIPE)
		return (execute_command(&node->data.redirection.child, shell, 1));
	if (node->data.redirection.type == REDIR_INPUT)
	{
		result = process_redirections(node, shell);
		if (node->fd_in > 2)
			return (node->fd_in);
		if (node->data.redirection.child
			&& node->data.redirection.child->type == NODE_COMMAND
			&& node->data.redirection.child->fd_in > 2)
			return (node->data.redirection.child->fd_in);
		return (result);
	}
	else if (node->data.redirection.type == REDIR_OUTPUT
		|| node->data.redirection.type == REDIR_APPEND)
		return (process_redirections(node, shell), -1);
	else
	{
		result = process_redirections(node, shell);
		return (result);
	}
}
