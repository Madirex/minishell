/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:40:36 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/11 19:21:33 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor/executor.h"

int				process_redirection(t_ast_node *node_cpy, t_shell *shell);
int				handle_node_command(t_ast_node *node_cpy, t_shell *shell,
					int *is_pipe);
t_cmd_context	create_cmd_context(t_ast_node *cmd,
					t_ast_node *right_node, int last_input_fd, int left_fd);
int				setup_command_fd(t_cmd_context *ctx,
					t_shell *shell, int is_pipe);
int				handle_command_output(t_ast_node *last_output,
					int cmd_fd, int fd_to_return);

/**
 * @brief Process pipe right redirection
 *
 * @param right_node the right node
 * @param left_fd the left fd
 * @param shell the shell struct
 * @param is_pipe if the command is a pipe
 * 
 * @return the fd of the out
 */
int	process_pipe_right_redirection(t_ast_node *right_node,
		int left_fd, t_shell *shell, int is_pipe)
{
	t_ast_node		*cmd;
	t_ast_node		*current;
	int				last_input_fd;
	t_cmd_context	ctx;

	current = right_node;
	cmd = NULL;
	last_input_fd = -1;
	while (current && current->type == NODE_REDIRECTION)
	{
		if (current->data.redirection.type == REDIR_INPUT
			|| current->data.redirection.type == REDIR_HEREDOC)
		{
			if (!process_redirection(current, shell))
				return (-1);
			else if (current->fd_in > 2)
				last_input_fd = current->fd_in;
		}
		cmd = process_right_redir_input(current, shell, &last_input_fd);
		if (cmd)
			break ;
		current = current->data.redirection.child;
	}
	ctx = create_cmd_context(cmd, right_node, last_input_fd, left_fd);
	return (setup_command_fd(&ctx, shell, is_pipe));
}

/**
 * @brief Find command node
 * 
 * @param current the current redirection node
 * 
 * @return the command node if found, NULL otherwise
 */
t_ast_node	*find_cmd_node(t_ast_node *current)
{
	if (current->data.redirection.child
		&& current->data.redirection.child->type == NODE_COMMAND)
		return (current->data.redirection.child);
	return (NULL);
}

/**
 * @brief Handle input redirection
 * 
 * @param current the current redirection node
 * @param shell the shell struct
 * @param last_input_fd pointer to last input fd
 * 
 * @return 1 if success, 0 otherwise
 */
int	handle_input_redirection(t_ast_node *current,
			t_shell *shell, int *last_input_fd)
{
	if (!process_redirection(current, shell))
		return (0);
	if (current->fd_in > 2)
	{
		*last_input_fd = current->fd_in;
		return (1);
	}
	else if (current->data.redirection.child
		&& current->data.redirection.child->fd_in > 2)
	{
		*last_input_fd = current->data.redirection.child->fd_in;
		return (1);
	}
	return (1);
}

/**
 * @brief Handle output redirection
 * 
 * @param current the current redirection node
 * @param last_output pointer to last output redirection node
 * 
 * @return 1 if success, 0 otherwise
 */
int	handle_output_redirection(t_ast_node *current,
			t_ast_node **last_output)
{
	int		fd;
	char	*clean_path;

	if (*last_output)
	{
		clean_path = handle_quotes((*last_output)->data.redirection.file);
		if (!clean_path)
			return (0);
		fd = open(clean_path, O_WRONLY | O_CREAT, 0644);
		free(clean_path);
		if (fd != -1)
			close(fd);
	}
	*last_output = current;
	return (1);
}

/**
 * @brief Execute command with redirections
 * 
 * @param cmd_node the command node
 * @param last_output the last output redirection node
 * @param last_input_fd the last input fd
 * @param shell the shell struct
 * 
 * @return the fd of the out or -1 on failure
 */
int	execute_cmd_with_redirections(t_ast_node *cmd_node,
			t_ast_node *last_output, int last_input_fd, t_shell *shell)
{
	int		is_pipe;
	int		cmd_fd;
	int		fd_to_return;

	fd_to_return = -1;
	if (last_input_fd > 2)
		cmd_node->fd_in = last_input_fd;
	is_pipe = 1;
	cmd_fd = handle_node_command(cmd_node, shell, &is_pipe);
	if (!last_output && cmd_fd >= 0)
	{
		fd_to_return = dup(cmd_fd);
		if (fd_to_return == -1)
			return (close(cmd_fd), -1);
	}
	if (cmd_fd < 0)
		return (-1);
	return (handle_command_output(last_output, cmd_fd, fd_to_return));
	if (cmd_node->fd_in > 2 && fd_to_return == -1)
		if (cmd_node->fd_in != cmd_fd)
			return (cmd_node->fd_in);
	if (fd_to_return == -1)
		return (1);
	return (fd_to_return);
}
