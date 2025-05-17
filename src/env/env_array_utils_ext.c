/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array_utils_ext.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:10:30 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/21 15:18:36 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env_array_utils_ext.c
 * @brief This file contains utility functions for handling environment variables
 * in the Minishell project.
 * It includes functions to join key-value pairs, free memory on error, and
 * convert environment variables to an array of strings.
 */
#include "env/env.h"
#include "minishell.h"

char	*ft_strjoin(const char *s1, const char *s2);
void	safe_free(void **ptr);

/**
 * @brief Joins a key and value into a single string in the format "key=value
 * @param key The key to join.
 * @param value The value to join.
 * @return A newly allocated string containing the key-value pair, or NULL on
 * failure.
 * 
 * @note This function first joins the key and "=" character, then joins the
 * result with the value. If any allocation fails, it returns NULL.
 * @note The caller must ensure that the key and value are not NULL.
 */
char	*join_key_value(const char *key, const char *value)
{
	char	*temp_str;
	char	*result;

	temp_str = ft_strjoin(key, "=");
	if (!temp_str)
		return (NULL);
	result = ft_strjoin(temp_str, value);
	safe_free((void **)&temp_str);
	return (result);
}

/**
 * @brief Frees the environment variable array on error.
 * @param envp The environment variable array to free.
 * @param i The index of the last successfully allocated string.
 * 
 * @note This function iterates through the array and frees each string up to
 * the index `i`. It then frees the array itself.
 * @note This function is used to clean up memory in case of allocation failure
 * during the creation of the environment variable array.
 * 
 */
void	free_envp_on_error(char **envp, int i)
{
	if (!envp || !*envp || i <= 0)
		return ;
	while (i > 0)
		safe_free((void **)&envp[--i]);
	safe_free((void **)&envp);
}
