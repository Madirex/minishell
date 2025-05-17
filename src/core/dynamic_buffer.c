/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:23:51 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/18 10:23:48 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/dynamic_buffer.h"

void	ft_error_msg(const char *prefix, const char *msg);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*safe_malloc(size_t size);

/**
 * @brief Initializes a dynamic buffer.
 * 
 * This function initializes a dynamic buffer with the specified initial
 * capacity.
 * 
 * @param buffer Pointer to the dynamic buffer structure.
 * @param initial_capacity Initial capacity of the buffer.
 * @return true if the buffer was successfully initialized, false otherwise.
 * 
 * @note The initial capacity must be greater than or equal to MIN_BUFFER_SIZE.
 * @note The returned structure must be freed after use to prevent memory leaks.
 */
bool	init_buffer(t_dynamic_buffer *buffer, size_t initial_capacity)
{
	if (!buffer)
	{
		ft_error_msg("Buffer", "Invalid buffer pointer");
		return (false);
	}
	if (initial_capacity < MIN_BUFFER_SIZE)
		initial_capacity = MIN_BUFFER_SIZE;
	buffer->data = safe_malloc(initial_capacity * sizeof(char));
	if (!buffer->data)
	{
		ft_error_msg("Buffer", "Memory allocation failed");
		buffer->size = 0;
		buffer->capacity = 0;
		return (false);
	}
	buffer->size = 0;
	buffer->capacity = initial_capacity;
	buffer->data[0] = '\0';
	return (true);
}

/**
 * @brief Expands the buffer capacity.
 * 
 * This function expands the buffer capacity by a factor of 2.
 * 
 * @param buffer Pointer to the dynamic buffer structure.
 * @return true if the buffer was successfully expanded, false otherwise.
 * 
 * @note The buffer must be initialized before calling this function.
 */
bool	expand_buffer(t_dynamic_buffer *buffer)
{
	size_t	new_capacity;
	char	*new_data;

	if (!buffer)
	{
		ft_error_msg("Buffer", "Invalid buffer pointer");
		return (false);
	}
	if (buffer->capacity > 0)
		new_capacity = buffer->capacity * 2;
	else
		new_capacity = MIN_BUFFER_SIZE;
	new_data = ft_realloc(buffer->data, buffer->size, new_capacity);
	if (!new_data)
	{
		ft_error_msg("Buffer", "Memory allocation failed");
		return (false);
	}
	buffer->data = new_data;
	buffer->capacity = new_capacity;
	return (true);
}

/**
 * @brief Appends data to the buffer.
 * 
 * This function appends the specified data to the buffer.
 * 
 * @param buffer Pointer to the dynamic buffer structure.
 * @param data Pointer to the data to append.
 * @param data_length Length of the data to append.
 * 
 * @return true if the data was successfully appended, false otherwise.
 * 
 * @note The buffer must be initialized before calling this function.
 */
bool	append_to_buffer(t_dynamic_buffer *buffer, const char *data,
	size_t data_length)
{
	size_t	new_capacity;
	char	*new_data;

	if (!buffer || !data)
		return (false);
	if (!buffer->data || buffer->capacity == 0)
		return (!init_buffer(buffer, MIN_BUFFER_SIZE));
	if (buffer->size + data_length >= buffer->capacity)
	{
		new_capacity = buffer->capacity * 2;
		new_data = ft_realloc(buffer->data, buffer->size, new_capacity);
		if (!new_data)
			return (ft_error_msg("Buffer", "Reallocation failed"), false);
		buffer->data = new_data;
		buffer->capacity = new_capacity;
	}
	ft_memcpy(buffer->data + buffer->size, data, data_length);
	buffer->size += data_length;
	buffer->data[buffer->size] = '\0';
	return (true);
}

/**
 * @brief Appends a single character to the buffer.
 * 
 * This function appends a single character to the buffer.
 * 
 * @param buffer Pointer to the dynamic buffer structure.
 * @param c The character to append.
 * 
 * @return true if the character was successfully appended, false otherwise.
 * 
 * @note The buffer must be initialized before calling this function.
 */
bool	append_char_to_buffer(t_dynamic_buffer *buffer, char c)
{
	if (!buffer || !buffer->data)
	{
		ft_error_msg("Buffer", "Invalid buffer pointer");
		return (false);
	}
	if (buffer->size + 1 >= buffer->capacity)
		expand_buffer(buffer);
	buffer->data[buffer->size++] = c;
	buffer->data[buffer->size] = '\0';
	return (true);
}

/**
 * @brief Frees the memory allocated for the dynamic buffer.
 * 
 * This function frees the memory allocated for the dynamic buffer and sets
 * the buffer's data pointer to NULL.
 * 
 * @param buffer Pointer to the dynamic buffer structure.
 * 
 * @return true if the buffer was successfully freed, false otherwise.
 * 
 */
bool	free_buffer(t_dynamic_buffer *buffer)
{
	if (!buffer || !buffer->data)
		return (false);
	if (buffer->data)
		safe_free((void **)&buffer->data);
	buffer->data = NULL;
	buffer->size = 0;
	buffer->capacity = 0;
	return (true);
}
