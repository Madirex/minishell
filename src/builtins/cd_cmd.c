/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:21:19 by anmateo-          #+#    #+#             */
/*   Updated: 2025/04/13 19:03:43 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cd_cmd.c
 * @brief Implementation of the cd command in the shell.
 * 
 * This file contains the implementation of the cd command, which is used
 * to change the current working directory of the shell.
 * It includes functions for handling the cd command, checking arguments,
 * updating environment variables, and preparing the path.
 */
#include "builtins/cd_cmd.h"

char	*ft_strjoin(const char *s1, const char *s2);

/**
 * @brief Update the environment variables for PWD and OLDPWD.
 * 
 * This function updates the OLDPWD and PWD environment variables
 * with the current working directory.
 * 
 * @param env A pointer to the environment structure.
 */
static void	update_env_vars(t_env *env)
{
	char	*cwd;

	env_set_value(env, "OLDPWD", get_env_value("PWD", env));
	cwd = get_current_directory();
	if (cwd)
	{
		env_set_value(env, "PWD", cwd);
		safe_free((void **)&cwd);
	}
}

/**
 * @brief Check the arguments for the cd command.
 * 
 * This function checks if the arguments passed to the cd command
 * are valid.
 * 
 * @param args The arguments passed to the cd command.
 */
static bool	check_handle_cd_args(char **args)
{
	if (!args || !args[0])
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (false);
	}
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}

/**
 * @brief Prepare the path for the cd command.
 * 
 * This function prepares the path for the cd command
 * by handling quotes and getting the absolute path.
 * 
 * @param args The arguments passed to the cd command.
 * @param env A pointer to the environment structure.
 * @param free_dir A pointer to an bool indicating whether
 * to free the directory.
 */
static char	*prepare_cd_path(char **args, t_env *env, bool *free_dir)
{
	char		*path;
	char		*original_arg;

	original_arg = args[1];
	args[1] = handle_quotes(args[1]);
	safe_free((void **)&original_arg);
	path = get_cd_path(args, env, free_dir);
	if (!path)
		return (NULL);
	if (path[0] != '/' && args[1] && ft_strcmp(args[1], "-") != 0)
	{
		path = get_absolute_path(path, args[1], free_dir);
		if (!path)
			return (NULL);
	}
	return (path);
}

/**
* @brief Execute the chdir command and update environment
* 
* This function changes the directory and updates environment variables
* 
* @param path The path to change to
* @param shell A pointer to the shell structure
* @param free_dir Boolean indicating if path should be freed
*/
static void	execute_cd(char *path, t_shell *shell, bool free_dir)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror("");
		shell->exit_status = 1;
	}
	else
		shell->exit_status = 0;
	update_env_vars(shell->env);
	if (free_dir)
		safe_free((void **)&path);
}

/**
* @brief Handle the cd command.
* 
* This function handles the cd command in the shell.
* It changes the current working directory to the specified path.
* 
* @param args The arguments passed to the cd command.
* @param shell A pointer to the shell structure.
*/
void	handle_cd(char **args, t_shell *shell)
{
	char	*path;
	bool	free_dir;

	free_dir = false;
	if (!check_handle_cd_args(args))
	{
		shell->exit_status = 1;
		return ;
	}
	path = prepare_cd_path(args, shell->env, &free_dir);
	if (!path)
	{
		shell->exit_status = 1;
		return ;
	}
	execute_cd(path, shell, free_dir);
}
