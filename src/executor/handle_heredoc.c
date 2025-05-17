/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:54:47 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/14 09:43:34 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor/executor.h"

void		setup_signals_for_heredoc(void);
int			create_pipe(int pipe_fd[2]);

/**
 * @brief Create pipe pair
 * 
 * @param pipe_fd the pipe fd
 * @param pipe_signal the pipe signal
 * 
 * @return 0 on success
 */
static int	create_pipe_pair(int pipe_fd[2], int pipe_signal[2])
{
	if (create_pipe(pipe_fd) == -1)
		return (-1);
	if (create_pipe(pipe_signal) == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	return (0);
}

/**
 * @brief Exit pipe with error
 *
 * @param pipe_fd the pipe fd
 * @param pipe_signal the pipe signal
 */
static void	exit_pipe_with_error(int pipe_fd[2], int pipe_signal[2])
{
	write(pipe_signal[1], "1", 1);
	close(pipe_signal[1]);
	close(pipe_fd[1]);
	exit(1);
}

/** 
 * @brief Handle signals for heredoc
 * 
 * @param pipe_fd the pipe fd
 * @param pipe_signal the pipe signal
 * @param delimiter the delimiter
 */
static void	handle_child_process(int pipe_fd[2],
	int pipe_signal[2], const char *delimiter)
{
	char	*line;

	close(pipe_signal[0]);
	close(pipe_fd[0]);
	setup_signals_for_heredoc();
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit_pipe_with_error(pipe_fd, pipe_signal);
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	close(pipe_signal[1]);
	exit(0);
}

/**
 * @brief Handle signals for heredoc
 * 
 * @param pipe_fd the pipe fd
 * @param pipe_signal the pipe signal
 * @param pid the pid
 */
static int	handle_parent_process(int pipe_fd[2], int pipe_signal[2], pid_t pid)
{
	int		status;
	char	buf[1];

	close(pipe_fd[1]);
	close(pipe_signal[1]);
	if (read(pipe_signal[0], buf, 1) > 0)
	{
		write(STDOUT_FILENO, "\n", 1);
		close(pipe_fd[0]);
		close(pipe_signal[0]);
		waitpid(pid, &status, WNOHANG);
		return (-1);
	}
	close(pipe_signal[0]);
	waitpid(pid, &status, WNOHANG);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
	{
		close(pipe_fd[0]);
		return (-1);
	}
	return (pipe_fd[0]);
}

/**
 * @brief Handle heredoc
 *
 * @param delimiter the delimiter
 * 
 * @return the fd
 */
int	handle_heredoc(const char *delimiter)
{
	int		pipe_fd[2];
	int		pipe_signal[2];
	pid_t	pid;

	if (create_pipe_pair(pipe_fd, pipe_signal) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(pipe_signal[0]);
		close(pipe_signal[1]);
		return (-1);
	}
	if (pid == 0)
		handle_child_process(pipe_fd, pipe_signal, delimiter);
	else
		return (handle_parent_process(pipe_fd, pipe_signal, pid));
	return (-1);
}
