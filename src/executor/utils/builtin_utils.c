/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:39:45 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/14 11:39:46 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor/executor.h"

void	handle_exit(char **args, t_shell *shell);
void	handle_unset(char **args, t_shell *shell);
void	handle_export(t_ast_node *node, t_shell *shell);
void	handle_echo(t_ast_node *node, t_shell *shell);
void	handle_pwd(t_ast_node *node);
void	handle_env(t_ast_node *node, t_env *env);
void	handle_cd(char **args, t_shell *shell);

/**
 * @brief Handle node command
 * 
 * @param node_cpy the node
 * @param shell the shell struct
 * @param is_pipe if the command is a pipe
 * 
 * @return the fd of the out
 */
int	is_builtin_command(const char *command_name)
{
	if (!command_name)
		return (0);
	if (ft_strcmp(command_name, "exit") == 0
		|| ft_strcmp(command_name, "echo") == 0
		|| ft_strcmp(command_name, "pwd") == 0
		|| ft_strcmp(command_name, "export") == 0
		|| ft_strcmp(command_name, "unset") == 0
		|| ft_strcmp(command_name, "env") == 0
		|| ft_strcmp(command_name, "cd") == 0)
		return (1);
	return (0);
}

/** 
 * @brief Handle builtin command
 *
 * @param node_cpy the node
 * @param shell the shell struct
 * 
 * @return the fd
 */
int	handle_builtin_command(t_ast_node *node_cpy, t_shell *shell)
{
	if (ft_strcmp(node_cpy->data.command.name, "exit") == 0)
		handle_exit(node_cpy->data.command.args, shell);
	else if (ft_strcmp(node_cpy->data.command.name, "echo") == 0)
		handle_echo(node_cpy, shell);
	else if (ft_strcmp(node_cpy->data.command.name, "pwd") == 0)
		handle_pwd(node_cpy);
	else if (ft_strcmp(node_cpy->data.command.name, "export") == 0)
		handle_export(node_cpy, shell);
	else if (ft_strcmp(node_cpy->data.command.name, "unset") == 0)
		handle_unset(node_cpy->data.command.args, shell);
	else if (ft_strcmp(node_cpy->data.command.name, "env") == 0)
		handle_env(node_cpy, shell->env);
	else if (ft_strcmp(node_cpy->data.command.name, "cd") == 0)
		handle_cd(node_cpy->data.command.args, shell);
	if (node_cpy->fd_in > 2)
		return (node_cpy->fd_in);
	return (-1);
}
