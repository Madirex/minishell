/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_ext.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:00:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 11:00:39 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file str_utils_ext.h
 * @brief This file contains the declarations of string utility functions.
 */

#ifndef STR_UTILS_EXT_H
# define STR_UTILS_EXT_H

# include "minishell.h"

char	*ft_strtok_r(char *str, const char *delim, char **saveptr);
char	*ft_strchr(const char *str, int c);
void	ft_strncpy(char *dest, const char *src, size_t n);
char	*skip_delimiters(char *str, const char *delim);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*handle_quotes(char *arg);

#endif
