/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command_pipe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:30:36 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/11 19:21:21 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor/executor.h"

int		process_redirection(t_ast_node *node_cpy, t_shell *shell);
int		handle_node_command(t_ast_node *node_cpy, t_shell *shell,
			int *is_pipe);
int		handle_heredoc(const char *delimiter);
int		execute_from_cmd_node(t_ast_node *cmd, t_shell *shell, int out_fd);
void	execute_child(t_ast_node *node, t_shell *shell, int pipe_fds[2]);
int		execute_parent(t_ast_node *node, t_shell *shell,
			int pipe_fds[2], pid_t pid);
int		handle_ls_case(t_ast_node *node, t_shell *shell);
int		process_pipe_left(t_ast_node *left_node, t_shell *shell);

/**
 * @brief Handles heredoc redirection execution.
 * 
 * @param node Redirection node with heredoc.
 * @param shell Shell state.
 * @return int Resulting file descriptor.
 */
int	handle_heredoc_redir(t_ast_node *node, t_shell *shell)
{
	int				heredoc_fd;
	t_ast_node		*cmd;
	int				fd;

	heredoc_fd = handle_heredoc(node->data.redirection.file);
	if (heredoc_fd <= 0)
		return (STDIN_FILENO);
	cmd = node->data.redirection.child;
	while (cmd && cmd->type == NODE_REDIRECTION)
		cmd = cmd->data.redirection.child;
	if (cmd && cmd->type == NODE_COMMAND)
	{
		cmd->fd_in = heredoc_fd;
		fd = execute_from_cmd_node(cmd, shell, node->fd_out);
		if (heredoc_fd > 2)
			close(heredoc_fd);
		return (fd);
	}
	close(heredoc_fd);
	return (STDIN_FILENO);
}

/**
 * @brief Handles input redirection execution.
 * 
 * @param node Redirection node with input.
 * @param shell Shell state.
 * @return int Resulting file descriptor.
 */
int	handle_input_redir(t_ast_node *node, t_shell *shell)
{
	t_ast_node	*cmd;
	int			dup_fd;

	if (!process_redirection(node, shell))
		return (STDIN_FILENO);
	cmd = node->data.redirection.child;
	while (cmd && cmd->type == NODE_REDIRECTION)
		cmd = cmd->data.redirection.child;
	if (!cmd || cmd->type != NODE_COMMAND)
		return (STDIN_FILENO);
	if (node->fd_in > 2)
	{
		cmd->fd_in = node->fd_in;
		if (cmd->data.command.args && cmd->data.command.args[1]
			&& node->fd_out != STDOUT_FILENO)
		{
			dup_fd = dup(cmd->fd_in);
			if (dup_fd != -1)
			{
				close(cmd->fd_in);
				cmd->fd_in = dup_fd;
			}
		}
	}
	return (execute_from_cmd_node(cmd, shell, node->fd_out));
}

/**
 * @brief Processes the right side of a pipe node (command execution).
 * 
 * @param right_node The right AST node (command).
 * @param left_fd The input file descriptor from the left pipe.
 * @param shell The shell state.
 * @param is_pipe Whether it's part of a pipe chain.
 * @return int The output file descriptor.
 */
int	process_pipe_right_command(t_ast_node *right_node,
	int left_fd, t_shell *shell, int is_pipe)
{
	t_ast_node	*temp;
	int			cmd_fd;

	if (right_node->type == NODE_COMMAND
		&& ft_strcmp(right_node->data.command.name, "ls") == 0
		&& left_fd == STDIN_FILENO)
		return (handle_ls_case(right_node, shell));
	right_node->fd_in = left_fd;
	temp = right_node;
	cmd_fd = execute_command(&temp, shell, is_pipe);
	if (cmd_fd >= 0)
		right_node->fd_in = cmd_fd;
	return (right_node->fd_in);
}

/**
 * @brief Process pipe right
 *
 * @param right_node the right node
 * @param left_fd the left fd
 * @param shell the shell struct
 * @param is_pipe if the command is a pipe
 * 
 * @return the fd of the out
 */
int	process_pipe_right(t_ast_node *right_node,
		int left_fd, t_shell *shell, int is_pipe)
{
	int	ret_fd;

	if (right_node->type == NODE_PIPE)
	{
		if (right_node->data.pipe.left)
			right_node->data.pipe.left->fd_in = left_fd;
		ret_fd = execute_command(&right_node, shell, is_pipe);
		if (left_fd > 2)
			close(left_fd);
		return (ret_fd);
	}
	else if (right_node->type == NODE_COMMAND)
	{
		ret_fd = process_pipe_right_command(right_node,
				left_fd, shell, is_pipe);
		if (left_fd > 2 && left_fd != ret_fd)
			close(left_fd);
		return (ret_fd);
	}
	else
		return (process_pipe_right_redirection(right_node,
				left_fd, shell, is_pipe));
}

/**
 * @brief Handles a pipe node by forking and managing I/O redirection.
 * 
 * @param node The AST node of type pipe.
 * @param shell The shell state.
 * @return int The resulting output file descriptor.
 */
int	handle_pipe_node(t_ast_node *node, t_shell *shell)
{
	int	left_fd;
	int	is_pipe;
	int	right_fd;

	is_pipe = 1;
	left_fd = STDIN_FILENO;
	if (node->data.pipe.left)
		left_fd = process_pipe_left(node->data.pipe.left, shell);
	if (node->data.pipe.right)
	{
		right_fd = process_pipe_right(node->data.pipe.right,
				left_fd, shell, is_pipe);
		if (left_fd > 2)
			close(left_fd);
		return (right_fd);
	}
	return (left_fd);
}
