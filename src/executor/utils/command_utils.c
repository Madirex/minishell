/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:35:42 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/27 20:35:43 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins/echo_cmd.h"
#include <sys/stat.h>

void	*safe_malloc(size_t size);
char	*ft_strjoin(const char *s1, const char *s2);
void	safe_free(void **ptr);
size_t	ft_strlen(const char *s);
char	*handle_quotes(char *arg);
char	*ft_strdup(const char *src);

/**
 * @brief Concatenates the arguments.
 *
 * This function concatenates the arguments.
 *
 * @param args The arguments.
 * @return The concatenated arguments.
 */
static char	*concatenate_args(char **args)
{
	char	*full_command;
	char	*temp;
	int		i;

	full_command = ft_strdup("");
	if (!full_command)
		return (NULL);
	i = 0;
	while (args[i])
	{
		temp = full_command;
		full_command = ft_strjoin(full_command, args[i]);
		if (!full_command)
			return (safe_free((void **)&temp), NULL);
		safe_free((void **)&temp);
		temp = full_command;
		full_command = ft_strjoin(full_command, " ");
		if (!full_command)
			return (safe_free((void **)&temp), NULL);
		safe_free((void **)&temp);
		i++;
	}
	return (full_command);
}

/**
 * @brief Counts the arguments.
 *
 * This function counts the arguments.
 *
 * @param args The arguments.
 * @return The count of arguments.
 */
static int	count_arguments(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

/**
 * @brief Generates the full command.
 *
 * This function generates the full command.
 *
 * @param node The node.
 * @return The full command.
 */
t_command	generate_full_command(t_ast_node *node)
{
	t_command	command;
	char		*full_command;
	int			i;
	int			j;

	command.args = NULL;
	command.name = NULL;
	full_command = concatenate_args(node->data.command.args);
	if (!full_command)
		return (command);
	command.name = ft_strdup(node->data.command.args[0]);
	command.args = safe_malloc(sizeof(char *)
			* (count_arguments(node->data.command.args) + 1));
	i = 0;
	j = 0;
	while (node->data.command.args[i])
	{
		if (ft_strcmp(node->data.command.args[i], ">") == 0
			|| ft_strcmp(node->data.command.args[i], "<") == 0)
			i += 2;
		else
			command.args[j++] = ft_strdup(node->data.command.args[i++]);
	}
	command.args[j] = NULL;
	return (safe_free((void **)&full_command), command);
}

/**
 * @brief Restore the original signal handlers.
 *
 * This function restores the original signal handlers for SIGINT and SIGQUIT
 * to their previous values.
 * 
 * @param cmd_data The command data structure containing
 * 	the original signal handlers.
 */
void	restore_signals(t_cmd_data cmd_data)
{
	signal(SIGINT, cmd_data.old_sigint);
	signal(SIGQUIT, cmd_data.old_sigquit);
}

/**
 * @brief Clean up resources after command execution.
 *
 * This function frees allocated memory and closes file descriptors
 * used during command execution.
 *
 * @param command The command structure containing arguments and metadata.
 * @param fd_in The file descriptor for input redirection.
 */
void	cleanup_resources(t_command command, int fd_in)
{
	free_array(command.args);
	safe_free((void **)&command.name);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
}
