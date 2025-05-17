/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:28:57 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/14 11:29:09 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file shlvl.c
 * @brief Functions to manage the SHLVL environment variable for the shell.
 *
 * This file contains functions to manage the SHLVL environment variable.
 *
 */

#include "minishell.h"

int		ft_atoi(const char *str);
char	*ft_itoa(const int n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
bool	is_numeric(const char *str);

/**
 * @brief Resets the SHLVL environment variable to 1.
 *
 * This function sets the SHLVL environment variable to a value of 1. If the
 * operation fails, an error message is displayed.
 * 
 * @param env A double pointer to the environment list.
 */
void	reset_shlvl(t_env **env)
{
	if (safe_setenv(env, "SHLVL", "1", 1) != 0)
		ft_putstr_fd("Error: Failed to reset SHLVL.\n", STDERR_FILENO);
}

/**
 * @brief Initializes the SHLVL environment variable.
 *
 * This function increments the SHLVL environment variable by 1.
 * If the SHLVL variable does not exist, it is created with a value of 1.
 *
 * @param env A double pointer to the environment list.
 * @note If the memory allocation for the new SHLVL value fails, an error
 * message is displayed.
 *
 * @see ft_atoi, ft_itoa
 */
void	initialize_shlvl(t_env **env)
{
	char	*shlvl_str;
	int		shlvl;
	char	*new_shlvl;

	shlvl_str = getenv("SHLVL");
	shlvl = 1;
	if (shlvl_str && is_numeric(shlvl_str))
		shlvl = ft_atoi(shlvl_str) + 1;
	new_shlvl = ft_itoa(shlvl);
	if (!new_shlvl)
	{
		ft_putstr_fd("Error: Failed to allocate memory for new SHLVL.\n",
			STDERR_FILENO);
		return ;
	}
	safe_setenv(env, "SHLVL", new_shlvl, 1);
	safe_free((void **)&new_shlvl);
}

/**
 * @brief Validates the SHLVL environment variable.
 *
 * This function checks if the SHLVL environment variable is a valid number
 * and within the range of an integer. If the value is invalid, an error
 * message is displayed.
 *
 * @param shlvl_str The string representation of the SHLVL value.
 * @param env A double pointer to the environment list.
 * @return int The SHLVL value if valid, -1 otherwise.
 */
static int	validate_shlvl(const char *shlvl_str, t_env **env)
{
	int	shlvl;

	if (!is_numeric(shlvl_str))
	{
		ft_putstr_fd("Error: SHLVL contains invalid characters.\n",
			STDERR_FILENO);
		return (-1);
	}
	shlvl = ft_atoi(shlvl_str);
	if (shlvl < 0 || shlvl == INT_MAX)
	{
		if (shlvl >= 1000)
		{
			ft_putstr_fd("Warning: SHLVL has reached the maximum value. \
				Reseting to 1\n", STDERR_FILENO);
			reset_shlvl(env);
		}
		else
			ft_putstr_fd("Error: SHLVL value is out of range.\n",
				STDERR_FILENO);
		return (-1);
	}
	return (shlvl);
}

/**
 * @brief Gets the incremented SHLVL value.
 * 
 * This function retrieves the current SHLVL value and increments it by 1.
 * If the SHLVL value is invalid, -1 is returned.
 * 
 * @param env A double pointer to the environment list.
 * @return int The incremented SHLVL value, or -1 on failure.
 * 
 */
static int	get_incremented_shlvl(t_env **env)
{
	char	*shlvl_str;
	int		shlvl;

	shlvl_str = getenv("SHLVL");
	shlvl = 1;
	if (shlvl_str)
	{
		shlvl = validate_shlvl(shlvl_str, env);
		if (shlvl == -1)
			return (-1);
		shlvl++;
	}
	return (shlvl);
}

/**
 * @brief Increments the SHLVL environment variable.
 *
 * This function calls get_incremented_shlvl to determine the new SHLVL value.
 * If the value is valid, it updates the environment variable.
 *
 * @param env A double pointer to the environment list.
 * @note If memory allocation or updating the environment variable fails, an
 * error message is displayed.
 *
 * @see get_incremented_shlvl, ft_itoa
 */
void	increment_shlvl(t_env **env)
{
	int		shlvl;
	char	*new_shlvl;

	shlvl = get_incremented_shlvl(env);
	if (shlvl == -1)
		return ;
	new_shlvl = ft_itoa(shlvl);
	if (!new_shlvl)
	{
		ft_putstr_fd("Error: Failed to allocate memory for new SHLVL.\n",
			STDERR_FILENO);
		return ;
	}
	if (safe_setenv(env, "SHLVL", new_shlvl, 1) != 0)
		ft_putstr_fd("Error: Failed to update SHLVL environment variable.\n",
			STDERR_FILENO);
	safe_free((void **)&new_shlvl);
}
