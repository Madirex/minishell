/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:40:50 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/24 18:41:52 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file mem_utils2.c
 * 
 * Functions to manipulate memory.
 */

#include "utils/mem_utils.h"

void	safe_free(void **ptr);

/**
 * @brief Frees an array of strings.
 *
 * This function frees each string in the array and then frees the array itself.
 * It is a utility function to clean up memory allocated for an array of strings.
 *
 * @param tokens The array of strings to be freed.
 */
void	free_array(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		safe_free((void **)&tokens[i]);
		i++;
	}
	safe_free((void **)&tokens);
}
