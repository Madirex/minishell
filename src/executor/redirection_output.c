/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:30:27 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/11 18:13:28 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file redirection_output.c
 * @brief Functions for handling output redirections
 * 
 * This file contains functions specific to processing output redirections,
 * which allow for writing command output to files.
 */

#include "minishell.h"
#include "executor/executor.h"

int			ft_write_fd_to_file(int fd, char *filePath, int append);
int			execute_command(t_ast_node **node, t_shell *shell, int is_pipe);
int			handle_node_command(t_ast_node *node_cpy, t_shell *shell,
				int *is_pipe);
t_ast_node	*check_special_node_types(t_ast_node *cmd, t_ast_node **cmd_node,
				t_ast_node **pipe_node);
t_ast_node	*select_return_node(t_ast_node *cmd_node, t_ast_node *pipe_node);

/**
 * @brief Finds an execution node in the AST by traversing the tree
 *
 * This function navigates the AST to find either a command node or a pipe node
 * that can be executed.
 *
 * @param cmd The root node to start searching from
 * @return A pointer to the found execution node, or NULL if none found
 */
t_ast_node	*find_execution_node_in_tree(t_ast_node *cmd)
{
	t_ast_node	*cmd_node;
	t_ast_node	*pipe_node;
	t_ast_node	*next_node;

	cmd_node = NULL;
	pipe_node = NULL;
	while (cmd)
	{
		next_node = check_special_node_types(cmd, &cmd_node, &pipe_node);
		if (!next_node)
			break ;
		cmd = next_node;
	}
	return (select_return_node(cmd_node, pipe_node));
}

/**
 * @brief Gets a file descriptor based on the execution node type
 *
 * This function handles obtaining the appropriate file descriptor for a
 * command or pipe node.
 *
 * @param exec_node The execution node (command or pipe)
 * @param shell The shell environment
 * @return The file descriptor for the execution node
 */
static int	get_fd_based_on_exec_type(t_ast_node *exec_node, t_shell *shell)
{
	int	is_pipe;
	int	fd;

	if (exec_node->type == NODE_COMMAND)
	{
		is_pipe = 1;
		fd = handle_node_command(exec_node, shell, &is_pipe);
	}
	else
		fd = execute_command(&exec_node, shell, 1);
	return (fd);
}

/**
 * @brief Determines if append mode should be used for file output
 *
 * This function checks if a redirection node is of type REDIR_APPEND.
 *
 * @param node_cpy The redirection node to check
 * @return 1 if append mode should be used, 0 otherwise
 */
static int	determine_append_flag(t_ast_node *node_cpy)
{
	if (node_cpy->data.redirection.type == REDIR_APPEND)
		return (1);
	return (0);
}

/**
 * @brief Handles the result of writing to a file
 *
 * This function checks if a write operation was successful and sets the
 * shell exit status accordingly.
 *
 * @param write_result The result of the write operation
 * @param shell The shell environment
 * @return 1 on success, 0 on failure
 */
static int	handle_write_result(int write_result, t_shell *shell)
{
	if (write_result == -1)
	{
		shell->exit_status = 1;
		return (0);
	}
	return (1);
}

/**
 * @brief Processes an output redirection
 *
 * This function handles an output redirection by executing the associated
 * command and writing its output to the specified file.
 *
 * @param node_cpy The output redirection node
 * @param shell The shell environment
 * @return 1 on success, 0 on failure
 */
int	process_output_redirection(t_ast_node *node_cpy, t_shell *shell)
{
	t_ast_node	*exec_node;
	int			fd;
	int			append_flag;
	int			write_result;

	if (node_cpy->data.redirection.type == REDIR_NONE)
		return (1);
	exec_node = find_execution_node_in_tree(node_cpy->data.redirection.child);
	if (!exec_node)
		return (0);
	fd = get_fd_based_on_exec_type(exec_node, shell);
	if (fd < 0)
		return (1);
	append_flag = determine_append_flag(node_cpy);
	write_result = ft_write_fd_to_file(fd, node_cpy->data.redirection.file,
			append_flag);
	close(fd);
	return (handle_write_result(write_result, shell));
}
