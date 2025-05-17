/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:45:43 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/11 16:54:10 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor/executor.h"

char	*find_command_in_path(const char *command, t_env *env);
char	*check_path(const char *path);
char	*ft_strtok(char *str, const char *delim);
char	*build_full_path(const char *dir, const char *command);

/**
 * @brief Gets the PATH environment variable.
 *
 * This function gets the PATH environment variable.
 *
 * @param env The environment variable.
 * @return A pointer to the PATH environment variable.
 */
static char	*get_path_from_env(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/**
 * @brief Finds the command in the PATH environment variable.
 *
 * This function finds the command in the PATH environment variable.
 *
 * @param command The command to find.
 * @param env The environment variable.
 * @return A pointer to the command if found, NULL otherwise.
 */
/**
 * @brief Validates and processes the command before path search
 *
 * @param command The command to validate
 * @return char* The processed command path if valid, NULL otherwise
 */
static char	*validate_command(const char *command)
{
	if (!command || command[0] == '\0')
		return (NULL);
	if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
		return (check_path(command));
	return (NULL);
}

/**
 * @brief Searches for executable command in a directory
 *
 * @param token Directory to search in
 * @param clean_command Command to search for
 * @return char* Full path if found and executable, NULL otherwise
 */
static char	*handle_path_result(char **path,
	char **clean_command, char *full_path)
{
	if (full_path)
	{
		safe_free((void **)&(*path));
		safe_free((void **)&(*clean_command));
		return (full_path);
	}
	return (NULL);
}

/**
 * @brief Searches for the command in a directory
 *
 * @param token Directory to search in
 * @param clean_command Command to search for
 * @return char* Full path if found, NULL otherwise
 */
static char	*search_in_directory(const char *token, const char *clean_command)
{
	char	*full_path;

	full_path = build_full_path(token, clean_command);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	safe_free((void **)&full_path);
	return (NULL);
}

/**
 * @brief Finds the command in the PATH environment variable
 *
 * This function searches for the command in each directory listed in PATH.
 * It handles command validation, path searching, and memory management.
 *
 * @param command The command to find
 * @param env The environment variable list
 * @return char* Full path to command if found, NULL otherwise
 */
char	*find_command_in_path(const char *command, t_env *env)
{
	char	*path;
	char	*token;
	char	*full_path;
	char	*clean_command;
	char	*validated_path;

	validated_path = validate_command(command);
	if (validated_path)
		return (validated_path);
	path = get_path_from_env(env);
	if (!path)
		return (NULL);
	clean_command = handle_quotes((char *)command);
	if (!clean_command)
		return (safe_free((void **)&path), NULL);
	token = ft_strtok(path, ":");
	while (token)
	{
		full_path = search_in_directory(token, clean_command);
		if (handle_path_result(&path, &clean_command, full_path))
			return (full_path);
		token = ft_strtok(NULL, ":");
	}
	safe_free((void **)&path);
	return (safe_free((void **)&clean_command), NULL);
}
