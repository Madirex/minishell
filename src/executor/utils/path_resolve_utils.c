/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolve_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:39:50 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/14 11:39:50 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor/executor.h"

/**
 * @brief Handles path errors
 * 
 * @param cmd The command
 * @param error_type The error type
 */
static void	handle_path_errors(char *cmd, int error_type)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	if (error_type == 0)
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	else if (error_type == 1)
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	else if (error_type == 2)
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	if (error_type == 0)
		exit(127);
	else
		exit(126);
}

/**
 * @brief Checks if the path is absolute
 * 
 * @param cmd The command
 * @return char* The absolute path
 */
static char	*check_absolute_path(char *cmd)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == -1)
		handle_path_errors(cmd, 0);
	if (S_ISDIR(path_stat.st_mode))
		handle_path_errors(cmd, 1);
	if (access(cmd, X_OK) == -1)
		handle_path_errors(cmd, 2);
	return (ft_strdup(cmd));
}

/**
 * @brief Resolves the command path
 *
 * @param command The command
 * @param shell The shell
 * 
 * @return char* The resolved path
 */
char	*resolve_command_path(t_command command, t_shell *shell)
{
	char		*cmd;
	char		*path;

	cmd = command.args[0];
	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		return (check_absolute_path(cmd));
	path = find_command_in_path(cmd, shell->env);
	return (path);
}
