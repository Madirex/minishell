/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:21:58 by anmateo-          #+#    #+#             */
/*   Updated: 2025/02/09 17:41:41 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file unset_cmd.c
 *
 * The unset command is used to remove environment variables from the shell's
 * environment.
 *
 */

#include "builtins/unset_cmd.h"

/**
 * @brief Handles the unset command for the minishell.
 *
 * This function processes the unset command, removing the specified environment
 * variable from the shell's environment.
 *
 * @param args An array of strings representing the arguments passed
 * to the unset command.
 * @param env A pointer to the environment structure containing
 * environment variables.
 *
 * @note The function removes the specified environment variable from the
 * environment list. If no variable is specified, the function does nothing.
 */
void	handle_unset(char **args, t_shell *shell)
{
	char	*var_name;
	int		i;

	i = 1;
	if (!args[1])
		return ;
	while (args[i])
	{
		var_name = ft_strdup(args[i]);
		shell->env = env_remove_node(shell->env, var_name);
		safe_free((void **)&var_name);
		i++;
	}
}
