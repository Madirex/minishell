/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:57:14 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/21 15:21:24 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env_array_utils.c
 * @brief Utilities for converting environment variables to an array format.
 * 
 * This file contains helper functions to manage the conversion of a linked list
 * of environment variables into an array of strings suitable for execution 
 * contexts.
 */

#include "env/env.h"
#include "minishell.h"

void	*safe_malloc(size_t size);
char	*join_key_value(const char *key, const char *value);
void	free_envp_on_error(char **envp, int i);

/**
 * @brief Counts the number of nodes in the environment linked list.
 * 
 * @param env Pointer to the head of the environment linked list.
 * @return The number of nodes in the linked list.
 */
static int	count_env_nodes(t_env *env)
{
	int		count;
	t_env	*temp;

	count = 0;
	temp = env;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

/**
 * @brief Allocates memory for the environment array.
 * 
 * @param node_count The number of nodes in the environment linked list.
 * @return A pointer to the newly allocated environment array, or NULL 
 * on failure.
 */
static char	**allocate_envp(int node_count)
{
	char	**envp;

	envp = safe_malloc(sizeof(char *) * (node_count + 1));
	if (!envp)
		return (NULL);
	return (envp);
}

/**
 * @brief Populates the environment array with key-value pairs from 
 * the linked list.
 * 
 * @param env Pointer to the head of the environment linked list.
 * @param envp The environment array to populate.
 * @return 0 on success, -1 on failure.
 */
static int	populate_envp(t_env *env, char **envp)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = env;
	while (temp)
	{
		if (temp->key && temp->value)
		{
			envp[i] = join_key_value(temp->key, temp->value);
			if (!envp[i])
			{
				free_envp_on_error(envp, i);
				return (-1);
			}
			i++;
		}
		temp = temp->next;
	}
	envp[i] = NULL;
	return (0);
}

/**
 * @brief Converts a linked list of environment variables to an array of strings.
 * 
 * This function creates an array of strings where each string is in the format
 * "key=value". The array is NULL-terminated.
 * 
 * @param env Pointer to the head of the environment linked list.
 * @return A pointer to the newly allocated environment array, or NULL 
 * on failure.
 */
char	**env_to_array(t_env *env)
{
	int		node_count;
	char	**envp;

	node_count = count_env_nodes(env);
	envp = allocate_envp(node_count);
	if (!envp)
		return (NULL);
	if (populate_envp(env, envp) == -1)
		return (NULL);
	return (envp);
}
