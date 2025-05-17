/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:49:19 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 10:51:33 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file char_utils.h
 * @brief This file contains utility functions for character handling.
 */

#ifndef CHAR_UTILS_H
# define CHAR_UTILS_H

# include <stdbool.h>

bool	ft_isalnum(int c);
bool	ft_isalpha(int c);
bool	ft_isdigit(int c);
bool	ft_isspace(char c);
bool	is_delimiter(char c, const char *delim);
bool	is_numeric(const char *str);

#endif
