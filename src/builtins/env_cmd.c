/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:21:32 by anmateo-          #+#    #+#             */
/*   Updated: 2025/04/13 18:15:18 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env_cmd.c
 * @brief This file contains the implementation of the env command in the shell.
 * It handles the environment variables and their display.
 * 
 * The env command is used to print all the environment variables in the shell.
 * It can also be used to set environment variables for a command.
 */

#include "builtins/env_cmd.h"

void	*safe_malloc(size_t size);
int		get_fd_from_str(void *str);

/** 
 * @brief Calculate the total length needed for the environment string
 * 
 * @param env A pointer to the environment structure
 * @return size_t The calculated total length
 */
static size_t	calculate_env_length(t_env *env)
{
	t_env	*current;
	size_t	total_len;

	current = env;
	total_len = 0;
	while (current)
	{
		if (current->value)
			total_len += ft_strlen(current->key)
				+ ft_strlen(current->value) + 2;
		current = current->next;
	}
	return (total_len);
}

/** 
 * @brief Build the environment string with all env variables
 * 
 * @param env A pointer to the environment structure
 * @return char* The built environment string or NULL on failure
 */
static char	*build_env_string(t_env *env)
{
	t_env	*current;
	char	*str;
	size_t	total_len;

	total_len = calculate_env_length(env);
	str = safe_malloc(total_len + 1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	current = env;
	while (current)
	{
		if (current->value)
		{
			ft_strcat(str, current->key);
			ft_strcat(str, "=");
			ft_strcat(str, current->value);
			ft_strcat(str, "\n");
		}
		current = current->next;
	}
	return (str);
}

/** 
 * @brief Handle the env command
 * 
 * This function processes the env command, which lists all environment variables
 * in the shell's environment.
 * 
 * @param node A pointer to the AST node representing the env command
 * @param env A pointer to the environment structure
 */
void	handle_env(t_ast_node *node, t_env *env)
{
	char	*str;

	str = build_env_string(env);
	if (!str)
		return ;
	if (node->fd_out != STDOUT_FILENO)
	{
		write(node->fd_out, str, ft_strlen(str));
		safe_free((void **)&str);
		return ;
	}
	node->fd_in = get_fd_from_str(str);
	safe_free((void **)&str);
	while (node->next && node->next->type == NODE_COMMAND
		&& ft_strcmp(node->next->data.command.name, "env") == 0)
		node = node->next;
}
