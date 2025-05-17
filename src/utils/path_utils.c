/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:23:03 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/01/07 19:16:57 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/path_utils.h"

char	*ft_strdup(const char *s);

/**
 * @brief Searches for a command in the PATH environment variable.
 * @param cmd Command to search for.
 * @param env Environment variables list.
 * @return The full path to the command if found, NULL otherwise.
 */
char	*resolve_command(const char *cmd, t_env *env)
{
	struct stat	st;
	char		*resolved_path;

	if (!cmd || !*cmd)
		return (NULL);
	if (stat(cmd, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			return (NULL);
		if (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
			return (ft_strdup(cmd));
	}
	resolved_path = search_in_path(cmd, env);
	return (resolved_path);
}
