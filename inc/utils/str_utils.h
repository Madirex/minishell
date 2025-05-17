/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:49:11 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 16:19:21 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file str_utils.h
 * @brief This file contains the declarations of string utility functions.
 * 
 * This file includes the declarations of functions for string manipulation,
 * comparison, and memory management. It also includes structures for handling
 * escape sequences and indices in strings.
 */

#ifndef STR_UTILS_H
# define STR_UTILS_H

# include "minishell.h"

/**
 * @brief Structure to hold parameters for escape sequence processing.
 * 
 * This structure is used to pass parameters to the function that processes
 * escape sequences in strings. It contains pointers to the string being
 * processed, the current index in the string, the result string, the
 * current index in the result string, and the active quote character.
 */
typedef struct s_escape_params
{
	char	*str;
	int		*i;
	char	*result;
	int		*j;
	char	active_quote;
}				t_escape_params;

/**
 * @brief Structure to hold indices for string processing.
 * 
 * This structure is used to hold the indices of characters in a string
 * during processing. It contains two integer indices, i and j, which
 * represent the current position in the string and the result string,
 * respectively.
 */
typedef struct s_indices
{
	int		i;
	int		j;
}				t_indices;

int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strdup(const char *s);
void	fill_str(char *str, int n, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dest, const char *src);
void	free_array(char **tokens);
bool	is_quote(char c);
bool	process_escape_in_quotes(t_escape_params *params);
void	toggle_active_quote(char c, char *active_quote);

#endif
