/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_buffer.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:09:03 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 10:45:27 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file dynamic_buffer.h
 * @brief This file contains the definitions for a dynamic buffer.
 * 
 * This file includes the definition of the dynamic buffer structure
 * and functions to manipulate it, such as appending data, expanding the buffer,
 * and freeing the buffer.
 */

#ifndef DYNAMIC_BUFFER_H
# define DYNAMIC_BUFFER_H

# include "minishell.h"
# include "types.h"
# define MIN_BUFFER_SIZE 256

bool	append_to_buffer(t_dynamic_buffer *buffer, const char *data,
			size_t data_length);
bool	append_char_to_buffer(t_dynamic_buffer *buffer, char c);
bool	expand_buffer(t_dynamic_buffer *buffer);
bool	free_buffer(t_dynamic_buffer *buffer);
bool	init_buffer(t_dynamic_buffer *buffer, size_t initial_capacity);

#endif