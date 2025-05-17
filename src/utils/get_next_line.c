/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:19:34 by ybolivar          #+#    #+#             */
/*   Updated: 2025/04/21 11:56:19 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file get_next_line.c
 * @brief This file contains the implementation of the get_next_line function.
 * 
 * This file includes the function definitions for reading lines from a file
 * descriptor. The get_next_line function reads a line from the file descriptor
 * and returns it as a string. The function handles the end of the file and
 * memory allocation for the line. It also includes utility functions for
 * string manipulation, such as ft_join_and_free, ft_clean_buffer, ft_get_line,
 * and ft_read_file.
 */

#include "utils/get_next_line.h"

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);

/**
 * @brief Joins two strings and frees the first one.
 * 
 * This function takes two strings, joins them together, and frees the first
 * string. It returns the newly allocated string that contains the concatenated
 * result.
 * 
 * @param buffer The first string to be joined.
 * @param sub_buffer The second string to be joined.
 * @return A pointer to the newly allocated string that contains the
 * concatenated result.
 */
static char	*ft_join_and_free(char *buffer, char *sub_bufer)
{
	char	*tmp;

	tmp = gnl_strjoin(buffer, sub_bufer);
	free(buffer);
	return (tmp);
}

/**
 * @brief Cleans the buffer by removing the part before the newline character.
 * 
 * This function takes a buffer string, finds the newline character, and
 * creates a new string that contains only the part after the newline
 * character. It frees the original buffer and returns the new string.
 * 
 * @param buffer The buffer string to be cleaned.
 * @return A pointer to the new string that contains the part after the
 * newline character. If the buffer is NULL or empty, it returns NULL.
 */
static char	*ft_clean_buffer(char *buffer)
{
	int		n;
	int		m;
	char	*sub_buffer;

	n = 0;
	m = 0;
	if (!buffer)
		return (NULL);
	while (buffer[n] != '\n' && buffer[n])
		n++;
	if (!buffer[n])
	{
		free(buffer);
		return (NULL);
	}
	sub_buffer = gnl_calloc(ft_strlen(buffer) - n + 1, sizeof(char));
	n++;
	while (buffer[n])
		sub_buffer[m++] = buffer[n++];
	free(buffer);
	return (sub_buffer);
}

/**
 * @brief Gets the line from the buffer.
 * 
 * This function takes a buffer string and extracts the line from it. It
 * allocates memory for the line and copies the characters from the buffer
 * until the newline character or the end of the string. It returns the
 * newly allocated line string.
 * 
 * @param buffer The buffer string to extract the line from.
 * @return A pointer to the newly allocated line string. If the buffer is
 * NULL or empty, it returns NULL.
 */
static char	*ft_get_line(char *buffer)
{
	char	*line;
	int		n;

	n = 0;
	if (!buffer[n])
		return (NULL);
	while (buffer[n] != '\n' && buffer[n])
		n++;
	line = gnl_calloc(n + 2, sizeof(char));
	n = 0;
	while (buffer[n] != '\n' && buffer[n])
	{
		line[n] = buffer[n];
		n++;
	}
	if (buffer[n] == '\n' && buffer[n])
		line[n] = '\n';
	return (line);
}

/**
 * @brief Reads the file and fills the buffer.
 * 
 * This function takes a file descriptor and reads the file in chunks of
 * BUFFER_SIZE. It appends the read data to the buffer until a newline
 * character is found or the end of the file is reached. It returns the
 * filled buffer.
 * 
 * @param fd The file descriptor to read from.
 * @param buffer The buffer to fill with the read data.
 * @return A pointer to the filled buffer. If an error occurs, it returns NULL.
 */
static char	*ft_read_file(int fd, char *buffer)
{
	int		read_bytes;
	char	*sub_buffer;

	read_bytes = 1;
	if (!buffer)
		buffer = gnl_calloc(1, 1);
	sub_buffer = gnl_calloc(sizeof(char), BUFFER_SIZE + 1);
	while (read_bytes > 0)
	{
		read_bytes = read(fd, sub_buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			free(sub_buffer);
			return (NULL);
		}
		sub_buffer[read_bytes] = '\0';
		buffer = ft_join_and_free(buffer, sub_buffer);
		if (ft_strchr(sub_buffer, '\n'))
			break ;
	}
	free(sub_buffer);
	return (buffer);
}

/**
 * @brief Reads the next line from the file descriptor.
 * 
 * This function takes a file descriptor and reads the next line from it.
 * It returns the line as a string. If an error occurs or the end of the
 * file is reached, it returns NULL.
 * 
 * @param fd The file descriptor to read from.
 * @return A pointer to the line string. If an error occurs or the end of
 * the file is reached, it returns NULL.
 */
char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = ft_read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_get_line(buffer);
	buffer = ft_clean_buffer(buffer);
	return (line);
}
