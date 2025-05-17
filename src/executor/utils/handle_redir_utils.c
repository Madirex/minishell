/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:39:53 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/14 11:39:53 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor/executor.h"

int	ft_write_fd_to_file(int fd, char *filePath, int append);
int	handle_output_file_write(t_ast_node *last_output, int cmd_fd);

/**
 * @brief Initialize command context with given parameters and
 *
 * @param ctx The command context to initialize
 * @param cmd The command node
 * @param right_node The right node of the command
 * @param last_input_fd The last input file descriptor
 * @param left_fd The left file descriptor
 */
t_cmd_context	create_cmd_context(t_ast_node *cmd,
	t_ast_node *right_node, int last_input_fd, int left_fd)
{
	t_cmd_context	ctx;

	ctx.cmd = cmd;
	ctx.right_node = right_node;
	ctx.last_input_fd = last_input_fd;
	ctx.left_fd = left_fd;
	return (ctx);
}

/**
* @brief Setup command file descriptor
* 
* @param ctx The command context
* @param shell The shell struct
* @param is_pipe If the command is a pipe
* 
* @return the fd of the command or -1 on failure
*/
int	setup_command_fd(t_cmd_context *ctx, t_shell *shell, int is_pipe)
{
	int	cmd_fd;

	if (!ctx->cmd)
		return (-1);
	if (ctx->last_input_fd != -1)
		ctx->cmd->fd_in = ctx->last_input_fd;
	else
		ctx->cmd->fd_in = ctx->left_fd;
	cmd_fd = handle_node_command(ctx->cmd, shell, &is_pipe);
	if (cmd_fd < 0)
		return (-1);
	return (process_right_redirection_output(ctx->right_node, cmd_fd, is_pipe));
}

/**
* @brief Execute command with redirections
* 
* @param cmd_node the command node
* @param last_output the last output redirection node
* @param last_input_fd the last input fd
* @param shell the shell struct
* 
* @return the fd of the command or -1 on failure
*/
int	handle_output_file_write(t_ast_node *last_output, int cmd_fd)
{
	char	*clean_path;

	clean_path = handle_quotes(last_output->data.redirection.file);
	if (!clean_path)
		return (-1);
	ft_write_fd_to_file(cmd_fd, clean_path,
		last_output->data.redirection.type == REDIR_APPEND);
	free(clean_path);
	return (1);
}

/**
* @brief Handle command output based on last_output and fd status
* 
* @param last_output the last output redirection node
* @param cmd_fd the command fd
* @param fd_to_return the fd to return
* 
* @return the fd of the out or -1 on failure
*/
int	handle_command_output(t_ast_node *last_output,
	int cmd_fd, int fd_to_return)
{
	if (last_output && cmd_fd >= 0)
	{
		if (handle_output_file_write(last_output, cmd_fd) == -1)
			return (-1);
		return (close(cmd_fd), 1);
	}
	else if (cmd_fd >= 0)
	{
		if (fd_to_return == -1)
			return (close(cmd_fd), 1);
		else
			return (close(cmd_fd), fd_to_return);
	}
	return (-1);
}
