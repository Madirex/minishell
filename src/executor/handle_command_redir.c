/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:35:36 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/11 19:21:28 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor/executor.h"

int	process_redirection(t_ast_node *node_cpy, t_shell *shell);
int	ft_write_fd_to_file(int fd, char *filePath, int append);

/**
 * @brief Process right redirection input
 *
 * @param current the current node
 * @param shell the shell struct
 * @param last_input_fd pointer to last input fd
 * 
 * @return the command node or NULL
 */
t_ast_node	*process_right_redir_input(t_ast_node *current,
		t_shell *shell, int *last_input_fd)
{
	if (current->data.redirection.type == REDIR_HEREDOC
		|| current->data.redirection.type == REDIR_INPUT)
	{
		if (!process_redirection(current, shell))
			return (NULL);
		if (current->fd_in > 2)
			*last_input_fd = current->fd_in;
		else if (current->data.redirection.child
			&& current->data.redirection.child->fd_in > 2)
			*last_input_fd = current->data.redirection.child->fd_in;
	}
	if (current->data.redirection.child
		&& current->data.redirection.child->type == NODE_COMMAND)
		return (current->data.redirection.child);
	return (NULL);
}

/**
 * @brief Check if there are more output redirections
 *
 * @param next the next redirection node
 *
 * @return 1 if there are more output redirections, 0 otherwise
 */
static int	has_more_output_redirections(t_ast_node *next)
{
	while (next && next->type == NODE_REDIRECTION)
	{
		if (next->data.redirection.type == REDIR_OUTPUT
			|| next->data.redirection.type == REDIR_APPEND)
			return (1);
		next = next->data.redirection.child;
	}
	return (0);
}

/**
 * @brief Handle a single output redirection
 *
 * @param current the current redirection node
 * @param cmd_fd the command fd
 * @param is_pipe if the command is a pipe
 *
 * @return the new command fd
 */
static int	handle_single_output_redirection(t_ast_node *current,
		int cmd_fd, int is_pipe)
{
	int	has_more_redirections;
	int	dup_fd;

	has_more_redirections = has_more_output_redirections(
			current->data.redirection.child);
	if (has_more_redirections || is_pipe)
	{
		dup_fd = dup(cmd_fd);
		ft_write_fd_to_file(cmd_fd, current->data.redirection.file,
			current->data.redirection.type == REDIR_APPEND);
		return (dup_fd);
	}
	ft_write_fd_to_file(cmd_fd, current->data.redirection.file,
		current->data.redirection.type == REDIR_APPEND);
	close(cmd_fd);
	return (-1);
}

/**
 * @brief Process right redirection output
 *
 * @param right_node the right node
 * @param cmd_fd the command fd
 * @param is_pipe if the command is a pipe
 * 
 * @return the fd of the out
 */
int	process_right_redirection_output(t_ast_node *right_node,
		int cmd_fd, int is_pipe)
{
	t_ast_node	*current;

	current = right_node;
	while (current && current->type == NODE_REDIRECTION)
	{
		if ((current->data.redirection.type == REDIR_OUTPUT
				|| current->data.redirection.type == REDIR_APPEND)
			&& cmd_fd >= 0)
			cmd_fd = handle_single_output_redirection(current, cmd_fd, is_pipe);
		current = current->data.redirection.child;
	}
	return (cmd_fd);
}
