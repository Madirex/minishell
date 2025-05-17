/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:33:19 by ybolivar          #+#    #+#             */
/*   Updated: 2025/04/21 11:56:32 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file get_next_line_utils.c
 * @brief This file contains utility functions for the get_next_line function.
 * 
 * This file includes the implementation of utility functions for reading lines
 * from a file descriptor. The functions include gnl_bzero, gnl_calloc,
 * and gnl_strjoin. These functions are used for memory
 * management and string manipulation in the get_next_line function.
 */

#include "utils/get_next_line.h"

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);

/**
 * @brief Sets the first len bytes of the memory area pointed to by str to zero.
 * 
 * This function is similar to the standard bzero function. It takes a pointer
 * to a memory area and sets the first len bytes to zero. It is used for
 * initializing memory before use.
 */
void	gnl_bzero(void *str, size_t len)
{
	unsigned char	*buf;

	buf = str;
	while (len--)
	{
		*buf++ = 0;
	}
}

/**
 * @brief Allocates memory for an array of count elements of size bytes each
 * and initializes all bytes to zero.
 * 
 * This function is similar to the standard calloc function. It takes the
 * number of elements and the size of each element as arguments. It allocates
 * memory for the array and initializes all bytes to zero. If the allocation
 * fails, it returns NULL. If the size or count is greater than SIZE_MAX,
 * it also returns NULL.
 * 
 * @param count The number of elements to allocate.
 * @param size The size of each element.
 * @return A pointer to the allocated memory, or NULL if the allocation fails.
 */
void	*gnl_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size >= SIZE_MAX || count >= SIZE_MAX)
		return (NULL);
	ptr = (void *)malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	gnl_bzero(ptr, (count * size));
	return (ptr);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*join;
	char	*send;

	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!join)
		return (NULL);
	send = join;
	while (*s1)
		*join++ = *s1++;
	while (*s2)
		*join++ = *s2++;
	*join = '\0';
	return (send);
}
