/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:35:51 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/11 16:53:44 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor/executor.h"
#include <errno.h>

/**
 * @brief Get File Descriptor from String
 *
 * @param str String
 *
 * @return File Descriptor
 */
int	get_fd_from_str(void *str)
{
	int	pipe_fd[2];

	if (str != NULL)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("Error creating pipe");
			return (-1);
		}
		write(pipe_fd[1], (char *)str, ft_strlen((char *)str));
		close(pipe_fd[1]);
		return (pipe_fd[0]);
	}
	else
		return (STDIN_FILENO);
}

/**
 * @brief Get File Descriptor from File
 *
 * @param filePath File Path
 *
 * @return File Descriptor
 */
int	get_fd_from_file(char *filePath)
{
	int	file_fd;

	file_fd = open(filePath, O_RDONLY);
	if (file_fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(filePath, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (-1);
	}
	return (file_fd);
}

/**
 * @brief Open file
 *
 * @param filePath File Path
 * @param append Append to File
 *
 * @return File Descriptor
 */
static int	open_file(char *filePath, int append)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	return (open(filePath, flags, 0644));
}

/**
 * @brief Write to File
 *
 * @param fd File Descriptor
 * @param file_fd File Descriptor
 *
 * @return 0 on Success, -1 on Failure
 */
static int	write_to_file(int fd, int file_fd)
{
	ssize_t	bytes_read;
	ssize_t	bytes_written;
	char	buffer[4096];

	if (fd < 0)
		return (-1);
	bytes_read = read(fd, buffer, sizeof(buffer));
	if (bytes_read < 0)
	{
		perror("read error");
		return (-1);
	}
	while (bytes_read > 0)
	{
		bytes_written = write(file_fd, buffer, bytes_read);
		if (bytes_written == -1)
			return (perror("write"), close(file_fd), -1);
		bytes_read = read(fd, buffer, sizeof(buffer));
		if (bytes_read < 0)
		{
			perror("read error");
			break ;
		}
	}
	return (0);
}

/**
 * @brief Write File Descriptor to File
 *
 * @param fd File Descriptor
 * @param filePath File Path
 * @param append Append to File
 *
 * @return 0 on Success, -1 on Failure
 */
int	ft_write_fd_to_file(int fd, char *filePath, int append)
{
	int	file_fd;

	file_fd = open_file(filePath, append);
	if (file_fd == -1)
		return (perror("open"), -1);
	if (write_to_file(fd, file_fd) == -1)
		return (-1);
	close(file_fd);
	return (0);
}
