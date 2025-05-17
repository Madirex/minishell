/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_execution_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:36:21 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/15 18:38:42 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Send data to more.
 *
 * This function sends data to more.
 *
 * @param fd File descriptor.
 * @param buffer Buffer.
 * @param size Size.
 * @param data More data.
 *
 * @return True if data was sent to more correctly, false if it failed.
 */
bool	send_data_to_more(int fd, char *buffer,
					size_t size, t_more_data *data)
{
	data->bytes_read = read(fd, buffer, size);
	if (data->bytes_read < 0)
	{
		close(data->pipe_fd[1]);
		waitpid(data->pid, NULL, 0);
		if (errno != EBADF)
			perror("read error");
		return (true);
	}
	while (data->bytes_read > 0)
	{
		write(data->pipe_fd[1], buffer, data->bytes_read);
		data->bytes_read = read(fd, buffer, size);
		if (data->bytes_read < 0)
		{
			if (errno != EBADF)
				perror("read error");
			break ;
		}
	}
	close(data->pipe_fd[1]);
	waitpid(data->pid, NULL, 0);
	return (true);
}

/**
 * @brief Initialize more process.
 *
 * This function initializes more process.
 *
 * @param data More data.
 * @return True if more process was initialized
 * correctly, false if it failed.
 */
bool	init_more_process(t_more_data *data)
{
	if (pipe(data->pipe_fd) != 0)
		return (false);
	data->pid = fork();
	if (data->pid == 0)
	{
		close(data->pipe_fd[1]);
		dup2(data->pipe_fd[0], STDIN_FILENO);
		close(data->pipe_fd[0]);
		data->args[0] = "more";
		data->args[1] = NULL;
		data->envp[0] = NULL;
		execve("/usr/bin/more", data->args, data->envp);
		exit(1);
	}
	return (data->pid > 0);
}
