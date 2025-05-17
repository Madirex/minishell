/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:55:01 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/11 18:13:01 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file compact_args.c
 * @brief Utility functions for argument handling
 * 
 * This file contains functions for manipulating command-line arguments.
 */
#include "minishell.h"

size_t	ft_strlen(const char *s);

/**
 * @brief Compacts an array of arguments by removing empty strings
 * 
 * This function iterates through an array of strings and removes any
 * empty strings, shifting the remaining strings to fill the gaps.
 * 
 * @param args The array of strings to compact
 * @param i_ptr Pointer to the current index in the array
 * @param j_ptr Pointer to the index where the next non-empty string 
 * should be placed
 * @return 0 on success
 * @return -1 on failure
 */
int	compact_args(char **args, int *i_ptr, int *j_ptr)
{
	int	i;
	int	j;

	i = *i_ptr;
	j = *j_ptr;
	while (args[i])
	{
		if (ft_strlen(args[i]) > 0)
		{
			args[j] = args[i];
			j++;
		}
		i++;
	}
	args[j] = NULL;
	*i_ptr = i;
	*j_ptr = j;
	return (0);
}
