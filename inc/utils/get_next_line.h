/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:44:54 by ybolivar          #+#    #+#             */
/*   Updated: 2025/04/21 11:55:04 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file get_next_line.h
 * @brief This file contains the definitions for the get_next_line function.
 * 
 * This file includes the function prototypes for reading lines from a file
 * descriptor. The get_next_line function reads a line from the file descriptor
 * and returns it as a string. The function handles the end of the file and
 * memory allocation for the line. It also includes utility functions for
 * string manipulation, such as gnl_bzero, gnl_calloc, and gnl_strjoin.
 */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

void	gnl_bzero(void *str, size_t len);
void	*gnl_calloc(size_t count, size_t size);
char	*get_next_line(int fd);
char	*gnl_strjoin(char const *s1, char const *s2);

#endif