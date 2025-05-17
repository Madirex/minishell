/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:45:49 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 18:54:08 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor/executor.h"

void		set_exit_code(t_shell *shell, int status);
int			handle_input_redir(t_ast_node *node, t_shell *shell);
int			handle_heredoc_redir(t_ast_node *node, t_shell *shell);

/**
 * @brief Executes the left node of a pipe (can be command or redirection).
 * 
 * @param left_node Left AST node.
 * @param shell Shell state.
 * @return int Output file descriptor from execution.
 */
int	process_pipe_left(t_ast_node *left_node, t_shell *shell)
{
	int			fd;
	t_ast_node	*temp;

	if (left_node->type == NODE_REDIRECTION)
	{
		if (left_node->data.redirection.type == REDIR_HEREDOC)
			return (handle_heredoc_redir(left_node, shell));
		if (left_node->data.redirection.type == REDIR_INPUT)
			return (handle_input_redir(left_node, shell));
	}
	temp = left_node;
	fd = execute_command(&temp, shell, 1);
	if (fd == -1)
		return (STDIN_FILENO);
	return (fd);
}

/**
 * @brief Handle pipe and wait
 *
 * @param shell the shell
 * @param pid the pid
 * @param data the pipe data
 * 
 * @return the fd
 */
int	handle_pipe_and_wait(t_shell *shell, pid_t pid, t_pipe_data data)
{
	int	status;
	int	sig;

	if (data.is_pipe)
		close(data.pipe_fds[1]);
	if (!data.is_pipe)
	{
		waitpid(pid, &status, 0);
		preserve_command_exit_status(shell, status);
		
		// Handle signals display
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT)
				write(STDERR_FILENO, "\n", 1);
			else if (sig == SIGQUIT)
				write(STDERR_FILENO, "Quit\n", 5);
		}
		return (STDIN_FILENO);
	}
	return (data.pipe_fds[0]);
}

/**
 * @brief Create pipe
 * 
 * @param pipe the fd
 * @return 0 on success
 */
int	create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		return (-1);
	return (0);
}

/**
 * @brief Executes the left (child) side of a pipe.
 * 
 * @param node The AST node representing the pipe.
 * @param shell The shell state.
 * @param pipe_fds Pipe file descriptors.
 */
void	execute_child(t_ast_node *node, t_shell *shell, int pipe_fds[2])
{
	int	left_fd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(pipe_fds[0]);
	if (node->data.pipe.left)
	{
		if (node->data.pipe.left->fd_out != STDOUT_FILENO)
			close(node->data.pipe.left->fd_out);
		node->data.pipe.left->fd_out = pipe_fds[1];
		left_fd = process_pipe_left(node->data.pipe.left, shell);
		if (left_fd > 2)
			close(left_fd);
	}
	close(pipe_fds[1]);
	exit(shell->exit_status);
}

/**
 * @brief Executes the right (parent) side of a pipe.
 * 
 * @param node The AST node representing the pipe.
 * @param shell The shell state.
 * @param pipe_fds Pipe file descriptors.
 * @param pid The child process PID.
 * @return int Final output file descriptor.
 */
int	execute_parent(t_ast_node *node, t_shell *shell,
				int pipe_fds[2], pid_t pid)
{
	int	status;
	int	right_fd;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	close(pipe_fds[1]);
	if (node->data.pipe.right)
	{
		node->data.pipe.right->fd_in = pipe_fds[0];
		if (node->fd_out != STDOUT_FILENO)
			node->data.pipe.right->fd_out = node->fd_out;
		right_fd = process_pipe_right(node->data.pipe.right,
				pipe_fds[0], shell, 1);
	}
	else
		right_fd = STDOUT_FILENO;
	close(pipe_fds[0]);
	waitpid(pid, &status, 0);
	preserve_command_exit_status(shell, status);
	return (right_fd);
}
