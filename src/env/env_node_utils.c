/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:01:46 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/25 19:35:25 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env_list_operations.c
 * 
 * This file contains functions for creating, appending, and searching
 * nodes in the environment list.
 * 
 * The environment list is a linked list that stores environment variables
 * as key-value pairs. Each node in the list contains a key, a value, and
 * a pointer to the next node in the list.
 */

#include "env/env.h"

void	*safe_malloc(size_t size);

/**
 * @brief Frees a single environment node.
 * 
 * This function releases all dynamically allocated memory for a given 
 * environment node, including its key and value, and the node itself.
 * 
 * @param node The environment node to free. Can safely be NULL.
 * 
 * @note If the node is NULL, the function does nothing.
 */
void	free_env_node(t_env *node)
{
	if (node)
	{
		if (node->is_freed)
			return ;
		node->is_freed = true;
		if (node->key)
			safe_free((void **)&node->key);
		if (node->value)
			safe_free((void **)&node->value);
		safe_free((void **)&node);
	}
}

t_env	*set_env_node(const char *key, const char *value)
{
	t_env	*new_node;

	new_node = (t_env *)safe_malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	if (!new_node->key || (value && !new_node->value))
	{
		ft_error_msg("initialize_env_node",
			"failed to initialize environment node");
		free_env_node(new_node);
		return (NULL);
	}
	new_node->is_freed = false;
	return (new_node);
}

/**
 * @brief Initializes a new node with a given key and value.
 * 
 * This function creates a new environment node and allocates memory for the
 * key and value. If memory allocation fails at any point, it cleans up
 * and returns NULL.
 * 
 * @param key The key for the environment variable.
 * @param value The value for the environment variable. Can be NULL.
 * @return t_env* The initialized node, or NULL on failure.
 * 
 * @note The caller is responsible for freeing the returned node when it is
 * no longer needed.
 */
t_env	*initialize_env_node(const char *key, const char *value)
{
	t_env	*new_node;

	if (!key)
	{
		ft_error_msg("initialize_env_node",
			"failed to initialize environment node");
		return (NULL);
	}
	new_node = set_env_node(key, value);
	if (!new_node)
	{
		ft_error_msg("initialize_env_node",
			"failed to initialize environment node");
		return (NULL);
	}
	return (new_node);
}
