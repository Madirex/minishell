/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:33:12 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/04 16:46:48 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file exit_cmd.c
 *
 * @brief Implementation of the exit built-in command for minishell.
 *
 * This file contains the implementation of the exit built-in command,
 * which terminates the minishell session. The command can take an optional
 * exit argument specifying the exit status. If no argument is provided,
 * it exits using the last known exit status stored in the environment.
 *
 * ### Behavior:
 * - If no arguments are provided: Use the last exit status.
 * - If the first argument is not exit: Print an error and exit with 255.
 * - If more than one argument is provided: Print an error and update the
 *   last exit status to 1 without exiting.
 * - If the argument is exit: Exit with the provided status, masked to
 *   fit the range [0, 255].
 *
 */

#include "builtins/exit_cmd.h"

void	free_env_list(t_env *head);
bool	ft_isdigit(int c);
void	ft_putstr_fd(const char *s, int fd);
int		ft_atoi(const char *str);
void	*safe_malloc(size_t size);
size_t	ft_strlen(const char *s);
void	safe_free(void *ptr);

/**
 * @brief Frees the environment list and exits the shell.
 * 
 * This function is responsible for cleaning up the environment list
 * and terminating the shell session. It prints "exit" to the standard
 * output if the shell is running in a terminal (tty). The exit status
 * is determined by the shell's exit status or defaults to 0 if the
 * shell pointer is null.
 * 
 * @param shell A pointer to the shell structure containing the environment
 *              and exit status.
 */
void	quit_shell(t_shell *shell)
{
	int	last_status;

	if (shell)
		last_status = shell->exit_status;
	else
		last_status = 0;
	if (shell && shell->env)
	{
		free_env_list(shell->env);
		shell->env = NULL;
	}
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	rl_clear_history();
	exit(last_status);
}

/**
 * @brief Checks if the given string is exit.
 *
 * This function determines whether the provided string consists solely
 * of exit characters.
 *
 * @param str The string to be checked.
 * @return true if the string is exit, false otherwise.
 *
 * @note An empty string or a string with only a sign ('+' or '-') is not
 * considered exit.
 */
bool	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (false);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Strips all quotes from a string for exit validation.
 *
 * Unlike strip_quotes which only removes surrounding quotes,
 * this function removes all quote characters from the string.
 *
 * @param str The input string.
 * @return A newly allocated string with all quotes removed.
 */
static char	*strip_all_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	result = safe_malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

/**
 * @brief Processes the exit command to terminate the shell session.
 *
 * This function handles the logic for the exit built-in command in
 * the minishell. Depending on the arguments provided, it determines
 * the appropriate exit status or updates the shell state in case of
 * errors.
 *
 * @param args An array of strings representing the arguments passed
 * to the exit command. The first element is "exit", followed by optional
 * arguments:
 *  - `args[1]`: A exit value specifying the exit status (optional).
 *  - `args[2]`: Additional arguments are treated as invalid and cause an error.
 * @param env A pointer to the environment structure containing:
 *  - `last_exit_status`: The status of the last executed command, used
 *    if no arguments are provided.
 *
 * @note If more than one argument is provided, the function does not exit
 * the shell but updates the `last_exit_status` to 1.
 */
void	handle_exit(char **args, t_shell *shell)
{
	int		exit_code;
	char	*exit_arg;

	if (!args[1])
		quit_shell(shell);
	exit_arg = strip_all_quotes(args[1]);
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		shell->exit_status = 1;
	}
	else if (!is_numeric(exit_arg))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		shell->exit_status = 2;
	}
	else
	{
		exit_code = ft_atoi(exit_arg) & 255;
		shell->exit_status = exit_code;
	}
	safe_free((void **)&exit_arg);
	quit_shell(shell);
}
