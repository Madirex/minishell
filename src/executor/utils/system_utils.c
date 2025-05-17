/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:25:01 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/11 19:25:01 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_sys_command(t_command command, t_shell *shell);

/**
 * @brief Setup child process IO
 *
 * @param fd_in the fd of the input
 * @param is_pipe if the command is a pipe
 * @param pipe_fds the pipe fds
 * @param node the ast node
 */
static void	setup_child_stdin(int fd_in)
{
	if (fd_in != STDIN_FILENO)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 (stdin)");
			exit(EXIT_FAILURE);
		}
		if (fd_in > 2)
			close(fd_in);
	}
}

/**
 * @brief Setup child process IO
 *
 * @param is_pipe if the command is a pipe
 * @param pipe_fds the pipe fds
 * @param node the ast node
 */
static void	setup_child_stdout(int is_pipe, int pipe_fds[2], t_ast_node *node)
{
	if (is_pipe)
	{
		if (node && node->fd_out != STDOUT_FILENO)
		{
			if (dup2(node->fd_out, STDOUT_FILENO) == -1)
			{
				perror("dup2 (stdout - node)");
				exit(EXIT_FAILURE);
			}
		}
		else if (pipe_fds[1] != STDOUT_FILENO)
		{
			if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
			{
				perror("dup2 (stdout - pipe)");
				exit(EXIT_FAILURE);
			}
		}
	}
	if (pipe_fds[0] > 2 && pipe_fds[0] != STDIN_FILENO)
		close(pipe_fds[0]);
	if (pipe_fds[1] > 2 && pipe_fds[1] != STDOUT_FILENO)
		close(pipe_fds[1]);
	if (node && node->fd_out > 2 && node->fd_out != STDOUT_FILENO)
		close(node->fd_out);
}

/**
 * @brief Setup child process IO
 * 
 * @param fd_in the fd of the input
 * @param is_pipe if the command is a pipe
 * @param pipe_fds the pipe fds
 * @param node the ast node
 */
void	setup_child_io(int fd_in, int is_pipe,
		int pipe_fds[2], t_ast_node *node)
{
	setup_child_stdin(fd_in);
	setup_child_stdout(is_pipe, pipe_fds, node);
}

/**
 * @brief Create child process
 * 
 * @return pid of child process
 */
pid_t	create_child_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	return (pid);
}

/**
 * @brief Handles special case for 'ls' command when piped.
 * 
 * @param node AST command node.
 * @param shell Shell state.
 * @return int Output file descriptor.
 */
int	handle_ls_case(t_ast_node *node, t_shell *shell)
{
	int				original_stdout;
	int				original_term;
	t_ast_node		*temp;
	int				cmd_fd;

	original_stdout = dup(STDOUT_FILENO);
	original_term = isatty(STDOUT_FILENO);
	if (original_term)
		dup2(original_stdout, STDOUT_FILENO);
	temp = node;
	cmd_fd = execute_command(&temp, shell, 0);
	if (original_stdout > 2)
		close(original_stdout);
	return (cmd_fd);
}
