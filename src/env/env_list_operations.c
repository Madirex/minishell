/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:01:46 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/22 20:01:14 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env.h"

void	*safe_malloc(size_t size);

bool	allocate_key(const char *env, size_t length, char **key)
{
	*key = (char *)safe_malloc(length + 1);
	if (!*key)
	{
		ft_error_msg("Error", "Failed to allocate memory for key");
		return (false);
	}
	ft_strncpy(*key, env, length);
	(*key)[length] = '\0';
	return (true);
}

bool	allocate_value(const char *value_start, char **value)
{
	*value = ft_strdup(value_start);
	if (!*value)
	{
		ft_error_msg("Error", "Failed to allocate memory for value");
		return (false);
	}
	return (true);
}

bool	update_if_duplicate(t_env *head, const char *key,
			const char *value, t_env *new_node)
{
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
		{
			safe_free((void **)&head->value);
			head->value = ft_strdup(value);
			free_env_node(new_node);
			return (true);
		}
		head = head->next;
	}
	return (false);
}

/**
* @brief Frees the memory allocated for the environment list.
*
* @param head The head of the environment list.
*/
void	free_env_list(t_env *head)
{
	t_env	*tmp;

	while (head != NULL)
	{
		tmp = head->next;
		free_env_node(head);
		head = tmp;
	}
	safe_free((void **)&head);
}

void	append_to_list(t_env *head, t_env *new_node)
{
	while (head->next)
		head = head->next;
	head->next = new_node;
}
