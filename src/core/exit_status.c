/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:56:13 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/31 14:17:47 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * * @file exit_status.c
 * * @brief Functions for managing the exit status of the shell.
 * 
 * * This file contains functions to retrieve and set the exit status of the
 * * shell, as well as to expand the "$?" variable in commands. The exit status
 * * is used to indicate the success or failure of command execution. The
 * * functions handle the exit status of child processes and provide a way to
 * * access the exit status from within the shell.
 */

#include "minishell.h"
#include "types.h"
#include <sys/wait.h>

char	*ft_itoa(int n);

/**
 * @brief Retrieves the exit status of the shell.
 * 
 * @param shell The shell instance.
 * @return The exit status of the shell.
 * 
 * This function returns the exit status of the shell. The exit status is
 * stored in the shell instance and is updated whenever a child process exits.
 * The exit status is typically used to indicate the success or failure of
 * a command execution. A value of 0 usually indicates success, 
 * while a non-zero value indicates an error or failure.
 * 
 */
int	get_exit_status(t_shell *shell)
{
	return (shell->exit_status);
}

/**
 * @brief Sets the exit code of the shell based on the status of a child process.
 * 
 * @param shell The shell instance.
 * @param status The status of the child process.
 * 
 * This function sets the exit code of the shell based on the status of a child
 * process. It checks if the child process exited normally or was terminated
 * by a signal. If the process exited normally, it retrieves the exit code
 * using WEXITSTATUS. If the process was terminated by a signal, it calculates
 * the exit code as 128 + signal number. The exit code is then stored in
 * the shell instance.
 * 
 */
void	set_exit_code(t_shell *shell, int status)
{
	int	code;
	int	sig;

	code = 0;
	sig = 0;
	if (WIFEXITED(status))
	{
		code = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		code = 128 + sig;
	}
	shell->exit_status = code;
}

/**
 * @brief Expands the "$?" variable in a command.
 * 
 * @param shell The shell instance.
 * @return The expanded value of "$?" as a string.
 * 
 * This function expands the "$?" variable in a command. The "$?" variable
 * represents the exit status of the last executed command. The function
 * retrieves the exit status from the shell instance and converts it to a
 * string using ft_itoa. The resulting string is returned to the caller.
 * 
 * @note The caller is responsible for freeing the returned string.
 * 
 */
char	*expand_dollar_question(t_shell *shell)
{
	int		code;
	char	*expanded;

	code = get_exit_status(shell);
	expanded = ft_itoa(code);
	return (expanded);
}
