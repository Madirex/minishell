/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:35:36 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/15 18:42:46 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor/executor.h"

int		compact_args(char **args, int *i_ptr, int *j_ptr);
int		handle_builtin_command(t_ast_node *node_cpy, t_shell *shell);
int		is_builtin_command(const char *command_name);

/**
 * @brief Handle node command
 *
 * @param node_cpy the node
 * @param shell the shell struct
 * @param is_pipe if the command is a pipe
 *
 * @return the fd of the out
 */
int	handle_node_command(t_ast_node *node_cpy, t_shell *shell, int *is_pipe)
{
	char	**args;
	int		is_pipe_value;
	int		i;
	int		j;

	if (!node_cpy || node_cpy->type != NODE_COMMAND)
		return (-1);
	args = node_cpy->data.command.args;
	i = 0;
	j = 0;
	if (!args)
		return (-1);
	is_pipe_value = compact_args(args, &i, &j);
	if (!node_cpy->data.command.name || !args[0])
		return (-1);
	if (is_pipe)
		is_pipe_value = *is_pipe;
	node_cpy->is_pipe = is_pipe_value;
	if (is_builtin_command(node_cpy->data.command.name))
		return (handle_builtin_command(node_cpy, shell));
	return (handle_system_cmd(node_cpy, shell, node_cpy->fd_in, is_pipe_value));
}

/**
 * @brief Execute command
 *
 * @param node the node
 * @param shell the shell struct
 * @param is_pipe if the command is a pipe
 *
 * @return the fd of the out
 */
int	execute_command(t_ast_node **node, t_shell *shell, int is_pipe)
{
	t_ast_node	*node_cpy;

	if (!node || !(*node))
		return (-1);
	node_cpy = *node;
	if (node_cpy->type == NODE_PIPE)
		return (handle_pipe_node(node_cpy, shell));
	if (node_cpy->type == NODE_COMMAND)
		return (handle_command_node(node_cpy, shell, is_pipe));
	if (node_cpy->type == NODE_REDIRECTION)
		return (handle_redirection_node(node_cpy, shell));
	return (-1);
}
