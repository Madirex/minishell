/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:18:41 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/16 18:43:49 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env_core.c
 * 
 * Core Environment Node Operations
 * 
 * This file contains the core functions for creating, removing, and appending
 * nodes in the environment linked list.
 */

#include "env/env.h"

static void	split_env_string(const char *env, char **key, char **value)
{
	char	*separator;
	size_t	key_length;

	separator = ft_strchr(env, '=');
	if (separator)
	{
		key_length = separator - env;
		if (!allocate_key(env, key_length, key))
		{
			*value = NULL;
			return ;
		}
		if (!allocate_value(separator + 1, value))
			safe_free((void **)&*key);
	}
	else
	{
		*key = ft_strdup(env);
		*value = NULL;
		if (!*key)
			ft_error_msg("Error", "Failed to allocate memory for key");
	}
}

/**
* @brief Converts an array of environment strings to a linked list.
*
* This function converts an array of environment strings to a linked list.
*
* @param envp The array of environment strings.
* @return A pointer to the head of the linked list.
*/
t_env	*env_to_linked_list(char **envp)
{
	t_env	*cp_env;
	char	*key;
	char	*value;

	cp_env = NULL;
	if (!envp || !*envp)
		return (create_default_env());
	while (*envp)
	{
		split_env_string(*envp, &key, &value);
		env_append_node(&cp_env, key, value);
		safe_free((void **)&key);
		if (value != NULL)
			safe_free((void **)&value);
		envp++;
	}
	return (cp_env);
}
