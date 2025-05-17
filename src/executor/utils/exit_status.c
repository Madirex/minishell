/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:00:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 18:55:51 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file exit_status_fix.c
 * @brief Fix for preserving correct exit status from external commands
 *
 * This file contains functions that ensure external commands' exit statuses
 * are correctly preserved and not overridden by shell syntax error handlers.
 */

#include "minishell.h"
#include "executor/executor.h"

/**
 * @brief Preserves the exit status of an external command
 *
 * This function makes sure the exit status of commands like 'ls'
 * is correctly preserved and not overridden by shell syntax errors.
 *
 * @param shell The shell structure
 * @param status The process status from waitpid
 */
void	preserve_command_exit_status(t_shell *shell, int status)
{
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}
