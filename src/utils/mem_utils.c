/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:36:33 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/24 18:41:59 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** 
 * @file mem_utils.c
 * 
 * Functions to manipulate memory.
 * 
 * This file contains the functions ft_memset and ft_memcpy.
 * The ft_memset function sets a block of memory to a specified value.
 * The ft_memcpy function copies a block of memory to another block of memory.
 * 
 * @see mem_utils.h
 */

#include "utils/mem_utils.h"

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_error_msg(MALLOC_ERR, "safe_malloc failed");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

/**
 * @brief Sets a block of memory to a specified value.
 *
 * This function sets the first n bytes of the memory area pointed to by ptr
 * to the specified value (interpreted as an unsigned char).
 *
 * @param ptr Pointer to the memory area to be set.
 * @param value Value to be set. The value is passed as an int, but 
 * it is converted to unsigned char.
 * @param num Number of bytes to be set to the value.
 * @return Pointer to the memory area ptr.
 */
void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)ptr;
	i = 0;
	if (ptr == NULL)
		return (NULL);
	while (i < num)
	{
		p[i] = (unsigned char)value;
		i++;
	}
	return (ptr);
}

/**
 * @brief Copies n bytes from memory area src to memory area dest.
 *
 * This function copies n bytes from the memory area pointed to by src
 * to the memory area pointed to by dest. The memory areas must not overlap.
 * If they do, the behavior is undefined.
 *
 * @param dest Pointer to the destination memory area.
 * @param src Pointer to the source memory area.
 * @param n Number of bytes to copy.
 * @return A pointer to the destination memory area dest.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (dest == src || n == 0)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

/**
 * @brief Reallocates memory for a block of memory.
 * 
 * This function reallocates memory for a block of memory pointed to by ptr.
 * The new block of memory has the specified size new_size.
 * If ptr is NULL, the function behaves like safe_malloc.
 * If new_size is 0, the function behaves like free.
 * 
 * @param ptr Pointer to the block of memory to be reallocated.
 * @param old_size The size of the old block of memory.
 * @param new_size The size of the new block of memory.
 * @return A pointer to the new block of memory.
 * @note The contents of the old block of memory are copied to the new block.
 */
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		safe_free((void **)&ptr);
		return (NULL);
	}
	new_ptr = safe_malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		if (old_size < new_size)
			ft_memcpy(new_ptr, ptr, old_size);
		else
			ft_memcpy(new_ptr, ptr, new_size);
		safe_free((void **)&ptr);
	}
	return (new_ptr);
}

void	safe_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
