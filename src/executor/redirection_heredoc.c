/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:30:27 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/11 18:11:44 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file redirection_heredoc.c
 * @brief Functions for handling heredoc redirections
 * 
 * This file contains functions specific to processing heredoc redirections,
 * which allow for reading input from the terminal into a command.
 */

#include "minishell.h"
#include "executor/executor.h"

void		print_fd(int fd);
int			handle_node_command(t_ast_node *node_cpy, t_shell *shell,
				int *is_pipe);
int			handle_heredoc(const char *delimiter);
int			ft_write_fd_to_file(int fd, char *filePath, int append);
t_ast_node	*find_output_redirection_in_chain(t_ast_node *cmd_node);

/**
 * @brief Processes a command with an output redirection
 *
 * This function handles a command that has both a heredoc input and
 * an output redirection. It executes the command with the heredoc as its
 * input and writes the command's output to the specified file.
 *
 * @param cmd_node The command node to execute
 * @param output_redir The output redirection node
 * @param fd_in The file descriptor for the heredoc input
 * @param shell The shell environment
 * @return 1 on success, 0 on failure
 */
static int	process_cmd_with_output(t_ast_node *cmd_node,
	t_ast_node *output_redir, int fd_in, t_shell *shell)
{
	int	is_pipe;
	int	cmd_fd;
	int	append_flag;
	int	write_result;

	cmd_node->fd_in = fd_in;
	is_pipe = 1;
	cmd_fd = handle_node_command(cmd_node, shell, &is_pipe);
	if (cmd_fd < 0)
		return (1);
	append_flag = (output_redir->data.redirection.type == REDIR_APPEND);
	write_result = ft_write_fd_to_file(cmd_fd,
			output_redir->data.redirection.file, append_flag);
	close(cmd_fd);
	if (write_result == -1)
	{
		shell->exit_status = 1;
		return (0);
	}
	return (1);
}

/**
 * @brief Process a command with heredoc input
 *
 * This function handles the execution of a command that uses heredoc input,
 * optionally with output redirection.
 *
 * @param cmd_node The command node to execute
 * @param output_redir The output redirection node (can be NULL)
 * @param heredoc_fd The file descriptor for the heredoc input
 * @param shell The shell environment
 * @return 1 on success, 0 on failure
 */
static int	process_command_with_heredoc(t_ast_node *cmd_node,
	t_ast_node *output_redir, int heredoc_fd, t_shell *shell)
{
	int	is_pipe;
	int	cmd_fd;

	cmd_node->fd_in = heredoc_fd;
	if (output_redir)
		return (process_cmd_with_output(cmd_node, output_redir,
				heredoc_fd, shell));
	is_pipe = 1;
	cmd_fd = handle_node_command(cmd_node, shell, &is_pipe);
	if (cmd_fd >= 0)
	{
		print_fd(cmd_fd);
		close(cmd_fd);
	}
	return (1);
}

/**
 * @brief Processes a heredoc redirection
 *
 * This function handles a heredoc redirection by setting up the heredoc,
 * finding any output redirections, and executing the associated command.
 *
 * @param node_cpy The heredoc redirection node
 * @param shell The shell environment
 * @return 1 on success, 0 on failure
 */
int	process_heredoc_redirection(t_ast_node *node_cpy, t_shell *shell)
{
	int			heredoc_fd;
	t_ast_node	*cmd_node;
	t_ast_node	*output_redir;

	heredoc_fd = handle_heredoc(node_cpy->data.redirection.file);
	if (heredoc_fd == -1)
		return (0);
	node_cpy->fd_in = heredoc_fd;
	cmd_node = node_cpy->data.redirection.child;
	output_redir = find_output_redirection_in_chain(cmd_node);
	cmd_node = node_cpy->data.redirection.child;
	while (cmd_node && cmd_node->type == NODE_REDIRECTION)
	{
		cmd_node->fd_in = heredoc_fd;
		cmd_node = cmd_node->data.redirection.child;
	}
	if (cmd_node && cmd_node->type == NODE_COMMAND)
	{
		return (process_command_with_heredoc(cmd_node,
				output_redir, heredoc_fd, shell));
	}
	close(heredoc_fd);
	return (0);
}
