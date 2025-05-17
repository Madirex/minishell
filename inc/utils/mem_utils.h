/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:38:04 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 10:53:51 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file mem_utils.h
 * @brief This file contains memory utility functions.
 * 
 * This file includes functions for memory manipulation, such as
 * setting memory, copying memory, reallocating memory, and safely freeing
 * memory. These functions are used throughout the shell to manage memory
 * efficiently and avoid memory leaks.
 */

#ifndef MEM_UTILS_H
# define MEM_UTILS_H

# include "minishell.h"

void	*ft_memset(void *ptr, int value, size_t num);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void	safe_free(void **ptr);
void	*safe_malloc(size_t size);

#endif