/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:30:27 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/11 18:03:56 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file redirection_input.c
 * @brief Functions for handling input redirections
 * 
 * This file contains functions specific to processing input redirections,
 * which allow for reading input from files.
 */

#include "minishell.h"
#include "executor/executor.h"

int			get_fd_from_file(char *filePath);
char		*handle_quotes(char *arg);
void		ft_putstr_fd(const char *s, int fd);
void		safe_free(void **ptr);

/**
 * @brief Finds the last input redirection in a chain of redirection nodes
 *
 * This function traverses a chain of redirection nodes to find the last
 * input redirection node, as this is the one that should be used for input.
 *
 * @param node The redirection node to start searching from
 * @return A pointer to the last input redirection node found
 */
static t_ast_node	*find_last_input_redirection(t_ast_node *node)
{
	t_ast_node	*last_input;
	t_ast_node	*current;

	last_input = node;
	current = node->data.redirection.child;
	while (current && current->type == NODE_REDIRECTION)
	{
		if (current->data.redirection.type == REDIR_INPUT)
			last_input = current;
		current = current->data.redirection.child;
	}
	return (last_input);
}

/**
 * @brief Propagates a file descriptor to all child nodes
 *
 * This function sets the fd_in field of all child nodes of a node to the
 * provided file descriptor, ensuring that all subsequent commands use this
 * input source.
 *
 * @param node The parent node
 * @param new_fd The file descriptor to propagate
 */
static void	propagate_fd_to_children(t_ast_node *node, int new_fd)
{
	t_ast_node	*child;

	child = node->data.redirection.child;
	while (child && child->type == NODE_REDIRECTION)
	{
		child->fd_in = new_fd;
		child = child->data.redirection.child;
	}
	if (child && child->type == NODE_COMMAND)
		child->fd_in = new_fd;
}

/**
 * @brief Sets up the input file descriptor for a redirection node
 *
 * This function handles cleaning the file path, opening the file descriptor,
 * and setting up the input file descriptors for the node and its children.
 *
 * @param node_cpy The redirection node to set up
 * @return The new file descriptor on success, -1 on failure
 */
static int	setup_input_fd(t_ast_node *node_cpy)
{
	char	*clean_path;
	int		new_fd;

	if (node_cpy->data.redirection.child->fd_in > 2)
		close(node_cpy->data.redirection.child->fd_in);
	clean_path = handle_quotes(node_cpy->data.redirection.file);
	if (!clean_path)
		return (-1);
	new_fd = get_fd_from_file(clean_path);
	safe_free((void **)&clean_path);
	if (new_fd == -1)
		return (-1);
	node_cpy->fd_in = new_fd;
	if (node_cpy->data.redirection.child)
		node_cpy->data.redirection.child->fd_in = new_fd;
	return (new_fd);
}

/**
 * @brief Finds the last input redirection and propagates its file descriptor
 *
 * This function finds the last input redirection in a chain and sets up the
 * file descriptor for it, propagating it to all child nodes.
 *
 * @param node_cpy The redirection node to start searching from
 * @return 1 on success, 0 on failure
 */
static int	find_last_input_and_propagate_fd(t_ast_node *node_cpy)
{
	t_ast_node	*last_input;
	int			new_fd;
	char		*clean_path;

	last_input = find_last_input_redirection(node_cpy);
	if (last_input != node_cpy)
	{
		clean_path = handle_quotes(node_cpy->data.redirection.file);
		if (!clean_path)
			return (0);
		new_fd = open(clean_path, O_RDONLY);
		safe_free((void **)&clean_path);
		if (new_fd == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(node_cpy->data.redirection.file, STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			return (0);
		}
		return (close(new_fd), 1);
	}
	new_fd = setup_input_fd(node_cpy);
	if (new_fd == -1)
		return (0);
	return (propagate_fd_to_children(node_cpy, new_fd), 1);
}

/**
 * @brief Processes an input redirection
 *
 * This function handles an input redirection by finding the last input
 * redirection in a chain and setting up the appropriate file descriptor.
 *
 * @param node_cpy The input redirection node
 * @param shell The shell environment
 * @return 1 on success, 0 on failure
 */
int	process_input_redirection(t_ast_node *node_cpy, t_shell *shell)
{
	int	success;

	success = find_last_input_and_propagate_fd(node_cpy);
	if (!success)
	{
		shell->exit_status = 1;
		return (0);
	}
	return (1);
}
