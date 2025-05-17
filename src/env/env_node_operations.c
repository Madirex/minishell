/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:01:46 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/01/07 19:03:19 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env.h"

/**
 * @file env_node_operations.c
 * @brief Core Environment List Operations
 *
 * This file contains functions for creating, appending, and searching
 * nodes in the environment list.
 *
 * The environment list is a linked list that stores environment variables
 * as key-value pairs. Each node in the list contains a key, a value, and
 * a pointer to the next node in the list.
 */

bool	update_if_duplicate(t_env *head, const char *key, const char *value,
			t_env *new_node);
void	append_to_list(t_env *head, t_env *new_node);

/**
 * @brief Finds an environment variable node by its key.
 * 
 * This function searches through the linked list of environment variables
 * to find the first node that matches the specified key.
 * 
 * @param env The head of the environment list to search in.
 * @param key The key to search for. Must not be NULL.
 * @return t_env* The found node, or NULL if not found.
 */
t_env	*find_env_variable(t_env *env, const char *key)
{
	if (!key || !env)
		return (NULL);
	while (env)
	{
		if (env->key && ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

/**
 * @brief Creates a new environment node with a key and value.
 * 
 * This function creates and initializes a new environment node with
 * the specified key and value. It uses the helper function to ensure
 * consistent memory allocation and error handling.
 * 
 * @param key The key of the environment variable.
 * @param value The value of the environment variable. Can be NULL.
 * @return t_env* A pointer to the newly created node, or NULL on failure.
 * 
 * @note The caller is responsible for freeing the returned node when it is
 * no longer needed.
 */
t_env	*env_create_node(const char *key, const char *value)
{
	return (initialize_env_node(key, value));
}

/**
 * @brief Creates and appends an empty node to the environment list.
 * 
 * This function creates a new node with a key and no value, and appends
 * it to the end of the environment list.
 * 
 * @param env The head of the environment list.
 * @param key The key of the new node.
 * @return t_env* The newly created node, or NULL on failure.
 * 
 * @note The function does nothing if the key is NULL.
 */
t_env	*env_create_empty_node(t_env *env, const char *key)
{
	t_env	*new_node;

	new_node = initialize_env_node(key, NULL);
	if (!new_node)
		return (NULL);
	while (env->next)
		env = env->next;
	env->next = new_node;
	return (new_node);
}

/**
 * @brief Removes a node from the environment list by its key.
 * 
 * This function searches for a node with the specified key in the
 * environment list and removes it. It properly frees the memory
 * associated with the removed node.
 * 
 * @param env The head of the environment list.
 * @param key The key of the node to remove.
 * @return t_env* The new head of the environment list.
 * 
 * @note If the key is not found, the function returns the original list.
 */
t_env	*env_remove_node(t_env *env, const char *key)
{
	t_env	*current;
	t_env	*prev;

	current = env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				env = current->next;
			free_env_node(current);
			return (env);
		}
		prev = current;
		current = current->next;
	}
	return (env);
}

/**
 * @brief Appends a new node to the end of the environment list.
 * 
 * This function creates a new node with the given key and value and
 * appends it to the end of the linked list. If the list is empty,
 * the new node becomes the head.
 * 
 * @param head A pointer to the head of the environment list.
 * @param key The key of the new node.
 * @param value The value of the new node. Can be NULL.
 * 
 * @note The function does nothing if the key is NULL.
 */
void	env_append_node(t_env **head, const char *key, const char *value)
{
	t_env	*new_node;

	new_node = initialize_env_node(key, value);
	if (!new_node)
	{
		ft_error_msg("minishell", "failed to create environment node");
		return ;
	}
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	if (!update_if_duplicate(*head, key, value, new_node))
		append_to_list(*head, new_node);
}
