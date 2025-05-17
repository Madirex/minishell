/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/14 11:10:00 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Safely sets an environment variable in the list.
 *
 * @param env Pointer to the environment list.
 * @param name Name of the environment variable.
 * @param value Value to set for the variable.
 * @param overwrite Flag indicating whether to overwrite existing values.
 * @return int 0 on success, -1 on failure.
 */
int	safe_setenv(t_env **env, const char *name, const char *value, int overwrite)
{
	t_env	*node;

	if (!env || !name || !*name || ft_strchr(name, '='))
		return (-1);
	node = find_env_variable(*env, name);
	if (node)
	{
		if (!overwrite)
			return (0);
		safe_free((void **)&node->value);
		node->value = ft_strdup(value);
		if (!node->value)
			return (-1);
	}
	else
		env_append_node(env, name, value);
	return (0);
}
