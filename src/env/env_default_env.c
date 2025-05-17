/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_default_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:37:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/16 18:49:11 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env_default_env.c
 * @brief Initializes default environment variables required by minishell.
 */

#include "env/env.h"

/**
 * @brief Adds the default PATH variable to the environment list.
 *
 * This function initializes the PATH variable with a default value,
 * ensuring the shell has a basic executable search path.
 *
 * @param default_env A double pointer to the environment linked list.
 */
static void	add_default_path(t_env **default_env)
{
	char	*key;
	char	*value;

	key = ft_strdup("PATH");
	value = ft_strdup(DEFAULT_PATH);
	env_append_node(default_env, key, value);
	safe_free((void **)&key);
	safe_free((void **)&value);
}

/**
 * @brief Adds the default SHLVL variable to the environment list.
 *
 * Sets the shell level (SHLVL) variable to 1 for the initial shell,
 * indicating it is the first-level instance of the shell.
 *
 * @param default_env A double pointer to the environment linked list.
 */
static void	add_default_shlvl(t_env **default_env)
{
	char	*key;
	char	*value;

	key = ft_strdup("SHLVL");
	value = ft_strdup("1");
	env_append_node(default_env, key, value);
	safe_free((void **)&key);
	safe_free((void **)&value);
}

/**
 * @brief Adds the default PWD variable to the environment list.
 *
 * Initializes the PWD variable with the current working directory,
 * providing context for relative path commands.
 *
 * @param default_env A double pointer to the environment linked list.
 */
static void	add_default_pwd(t_env **default_env)
{
	char	*key;
	char	*pwd;

	key = ft_strdup("PWD");
	pwd = getcwd(NULL, 0);
	env_append_node(default_env, key, pwd);
	safe_free((void **)&key);
	safe_free((void **)&pwd);
}

/**
 * @brief Adds the default TERM variable to the environment list.
 *
 * Sets the terminal type variable TERM to ensure basic terminal compatibility.
 *
 * @param default_env A double pointer to the environment linked list.
 */
static void	add_default_term(t_env **default_env)
{
	char	*key;
	char	*value;

	key = ft_strdup("TERM");
	value = ft_strdup("xterm-256color");
	env_append_node(default_env, key, value);
	safe_free((void **)&key);
	safe_free((void **)&value);
}

/**
 * @brief Creates and initializes the default environment for minishell.
 *
 * This function initializes essential environment variables required by
 * minishell when the external environment is not available or is incomplete.
 *
 * @return t_env* A pointer to the head of the newly created environment list.
 */
t_env	*create_default_env(void)
{
	t_env	*default_env;

	default_env = NULL;
	add_default_path(&default_env);
	add_default_shlvl(&default_env);
	add_default_pwd(&default_env);
	add_default_term(&default_env);
	return (default_env);
}
