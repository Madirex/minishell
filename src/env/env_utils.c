/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:22:37 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/01 09:47:07 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env_utils.c
 * 
 * This file contains utility functions for working with environment variables.
 * 
 * The environment list is a linked list that stores environment variables
 * as key-value pairs. Each node in the list contains a key, a value, and
 * a pointer to the next node in the list.
 * 
 * The functions in this file provide basic operations for managing the
 * environment list, such as setting and getting values, and initializing
 * the list with default values.
 */

#include "env/env.h"
#include "core/dynamic_buffer.h"
#include "types.h"

bool	init_buffer(t_dynamic_buffer *buffer, size_t initial_capacity);

/**
 * @brief Updates the value of an existing environment variable.
 *
 * @param env The environment list to search in.
 * @param key The key of the environment variable to update.
 * @param value The new value to set.
 *
 * @note This function assumes the key exists in the environment list.
 * It frees the old value and allocates memory for the new value.
 */
static void	update_existing_env_value(t_env *env,
	const char *key, const char *value)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			safe_free((void **)&current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
}

/**
 * @brief Appends a new environment variable to the end of the environment list.
 *
 * @param env Pointer to the environment list.
 * @param key The key of the new environment variable.
 * @param value The value of the new environment variable.
 *
 * @note This function creates a new node and appends it to the end of the list.
 * If the list is empty, the new node becomes the head of the list.
 */
static void	append_new_env_value(t_env **env,
	const char *key, const char *value)
{
	t_env	*current;
	t_env	*last;
	t_env	*new_node;

	current = *env;
	last = NULL;
	while (current)
	{
		last = current;
		current = current->next;
	}
	new_node = initialize_env_node(key, value);
	if (!new_node)
		return ;
	if (!last)
		*env = new_node;
	else
		last->next = new_node;
}

/**
 * @brief Sets or updates an environment variable in the environment list.
 *
 * @param env The environment list to modify.
 * @param key The key of the environment variable to set.
 * @param value The value to set for the environment variable.
 *
 * @note If the key already exists in the environment list, its value is updated.
 * If the key doesn't exist, a new environment variable is appended to the list.
 * The function handles memory allocation for storing the new value.
 * If any parameter is NULL, the function returns without making any changes.
 */
void	env_set_value(t_env *env, const char *key, const char *value)
{
	t_env	*current;

	if (!env || !key || !value)
		return ;
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			update_existing_env_value(env, key, value);
			return ;
		}
		current = current->next;
	}
	append_new_env_value(&env, key, value);
}

/**
 * @brief Gets the value of an environment variable.
 *
 * @param key The key to search for.
 * @param env The environment list to search in.
 * @return char* The value if found, NULL otherwise.
 * 
 * @note The function returns NULL if the key is not found.
 */
char	*get_env_value(const char *key, t_env *env)
{
	t_env	*node;

	node = find_env_variable(env, key);
	if (node)
		return (node->value);
	else
		return (NULL);
}

/**
 * @brief Initializes a basic environment with the current working directory.
 * @param env The environment list to initialize.
 * 
 * @note This function initializes the PWD environment variable with the
 * current working directory.
 */
void	init_basic_env(t_env **env)
{
	char	*pwd;
	char	buffer[PATH_MAX];

	if (!env)
		return ;
	pwd = getcwd(buffer, PATH_MAX);
	if (pwd)
		env_append_node(env, "PWD", pwd);
	env_append_node(env, "?", "0");
	safe_free((void **)&pwd);
}
