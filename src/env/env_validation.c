/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:00:57 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/02/09 19:42:34 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env.h"

void	*safe_malloc(size_t size);

/**
 * @brief Checks if the given environment variable name is valid.
 *
 * This function verifies whether the provided environment variable name
 * adheres to the rules for valid environment variable names. Typically,
 * these rules include starting with a letter or underscore, followed by
 * letters, digits, or underscores.
 *
 * @param name The environment variable name to validate.
 * @return true if the name is valid, false otherwise.
 */
bool	is_valid_env_name(const char *name)
{
	size_t	i;

	if (!name || !name[0])
		return (false);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (false);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Extracts the name of an environment variable from a given string.
 *
 * This function takes a string representing an environment variable in the
 * format "NAME=VALUE" and extracts the "NAME" part of the string.
 *
 * @param var The input string representing the environment variable.
 * It should be in the format "NAME=VALUE".
 * 
 * @return A newly allocated string containing the name of the environment
 * variable. The caller is responsible for freeing this string.
 */
char	*get_env_name(const char *var)
{
	size_t	len;
	char	*name;

	len = 0;
	while (var[len] && (ft_isalnum(var[len]) || var[len] == '_'))
		len++;
	if (len == 0)
		return (NULL);
	name = safe_malloc(len + 1);
	if (!name)
		return (NULL);
	ft_strncpy(name, var, len);
	name[len] = '\0';
	return (name);
}
