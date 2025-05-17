/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:25:25 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/22 19:48:26 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/path_search.h"

char	*get_env_value(const char *key, t_env *env);
char	*ft_strdup(const char *s);
char	*ft_strtok_r(char *str, const char *delim, char **saveptr);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	safe_free(void **ptr);
void	*safe_malloc(size_t size);

/**
 * @brief Checks the given path.
 *
 * This function takes a path as input and performs necessary checks to 
 * determine its validity or existence.
 *
 * @param path The path to be checked.
 * @return A pointer to a character string representing the checked path.
 */
char	*check_path(const char *path)
{
	struct stat	st;
	char		*dup_path;

	if (stat(path, &st) == 0 && (st.st_mode & S_IXUSR))
	{
		dup_path = ft_strdup(path);
		if (!dup_path)
			return (NULL);
		return (dup_path);
	}
	return (NULL);
}

/**
 * @brief Joins the token and command to form a full path.
 *
 * This function takes a token and a command and concatenates them to form
 * a full path to the command.
 *
 * @param token The token to be used as the base path.
 * @param cmd The command to be appended to the token.
 * @return A pointer to a character string representing the full path.
 */
char	*join_path(const char *token, const char *cmd)
{
	char	*full_path;
	size_t	token_len;
	size_t	cmd_len;

	token_len = ft_strlen(token);
	cmd_len = ft_strlen(cmd);
	full_path = safe_malloc(token_len + cmd_len + 2);
	if (!full_path)
		return (NULL);
	ft_memcpy(full_path, token, token_len);
	full_path[token_len] = '/';
	ft_memcpy(full_path + token_len + 1, cmd, cmd_len);
	full_path[token_len + 1 + cmd_len] = '\0';
	return (full_path);
}

/**
 * @brief Processes the token to check for the command.
 * 
 * This function takes a token, a command, and a duplicate of the path, and
 * processes the token to check for the command. If the command is found, the
 * function returns the full path to the command. If the command is not found,
 * the function returns NULL.
 * 
 * @param token The token to be processed.
 * @param cmd The command to be checked.
 * @param path_dup A duplicate of the path.
 */
char	*check_command(const char *token, const char *cmd, char *path_dup)
{
	char	*full_path;
	char	*checked_path;

	full_path = join_path(token, cmd);
	if (!full_path)
	{
		safe_free((void **)&path_dup);
		return (NULL);
	}
	checked_path = check_path(full_path);
	if (checked_path)
	{
		safe_free((void **)&full_path);
		safe_free((void **)&path_dup);
		return (checked_path);
	}
	safe_free((void **)&full_path);
	return (NULL);
}

/**
 * @brief Searches for the given command in the system PATH.
 *
 * This function takes a command and an environment structure, and searches
 * for the command in the directories listed in the PATH environment variable.
 * If the command is found, the function returns the full path to the command.
 * If the command is not found, the function returns NULL.
 *
 * @param cmd The command to search for.
 * @param env The environment structure containing the PATH variable.
 * @return A string containing the full path to the command if found, 
 * or NULL if not found.
 */
char	*search_in_path(const char *cmd, t_env *env)
{
	char	*path_var;
	char	*path_dup;
	char	*token;
	char	*saveptr;
	char	*result;

	path_var = get_env_value("PATH", env);
	if (!path_var)
		return (NULL);
	path_dup = ft_strdup(path_var);
	if (!path_dup)
		return (NULL);
	token = ft_strtok_r(path_dup, ":", &saveptr);
	while (token)
	{
		result = check_command(token, cmd, path_dup);
		if (result)
			return (result);
		token = ft_strtok_r(NULL, ":", &saveptr);
	}
	safe_free((void **)&path_dup);
	return (NULL);
}
