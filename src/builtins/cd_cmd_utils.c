/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:25:25 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/13 19:07:42 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cd_cmd_utils.c
 * @brief Utility functions for the cd command in the shell.
 * 
 * This file contains utility functions for the cd command in the shell.
 * It includes functions for handling the OLDPWD environment variable,
 * getting the current working directory, and preparing the path for cd.
 */

#include "builtins/cd_cmd.h"

char	*ft_strjoin(const char *s1, const char *s2);

/**
 * @brief Get the current working directory.
 * 
 * This function retrieves the current working directory of the process.
 * It allocates memory for the directory string and returns it.
 * 
 * @return A pointer to the current working directory string.
 * 
 * @param path The path to be converted to absolute.
 * @param arg The argument to be appended to the path.
 * @param free_dir A pointer to an bool indicating whether 
 * to free the directory.
 */
char	*get_absolute_path(char *path, char *arg, bool *free_dir)
{
	char	*cwd;
	char	*tmp;

	cwd = get_current_directory();
	if (!cwd)
		return (NULL);
	tmp = ft_strjoin(cwd, "/");
	safe_free((void **)&cwd);
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, arg);
	safe_free((void **)&tmp);
	if (!path)
		return (NULL);
	*free_dir = true;
	return (path);
}

/**
* @brief Handle oldpwd
* 
* This function handles the OLDPWD environment variable.
* 
* @param env A pointer to the environment structure containing
* environment variables.
* @return A pointer to the old working directory.
*/
char	*handle_oldpwd(t_env *env)
{
	char	*path;
	char	*oldpwd;

	oldpwd = get_env_value("OLDPWD", env);
	if (!oldpwd)
	{
		write(2, "Error: cd: OLDPWD not set\n", 26);
		return (NULL);
	}
	path = ft_strdup(oldpwd);
	if (!path)
	{
		write(2, "Error: cd: OLDPWD not set\n", 26);
		return (NULL);
	}
	printf("%s\n", path);
	env_set_value(env, "OLDPWD", get_env_value("PWD", env));
	return (path);
}

/**
 * @brief Get the path for the cd command.
 * 
 * This function retrieves the path for the cd command based on the
 * provided arguments.
 * 
 * @param args The arguments passed to the cd command.
 * @param env A pointer to the environment structure.
 * @param free_dir A pointer to an unsigned int to indicate if the path
 * should be freed.
 */
char	*get_cd_path(char **args, t_env *env, bool *free_dir)
{
	char	*path;

	if (!args[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			return (NULL);
		}
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		path = handle_oldpwd(env);
		if (!path)
			return (NULL);
		*free_dir = 1;
	}
	else
		path = args[1];
	return (path);
}
