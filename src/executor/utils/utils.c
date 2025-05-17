/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:25:18 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/15 18:04:14 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file utils.c
 * @brief Utility functions for the minishell project
 * 
 * This file contains utility functions for building full paths,
 * finding execution nodes, and handling file descriptors.
 * These functions are used throughout the minishell project to manage
 * command execution and redirection.
 */

#include "minishell.h"

char	*ft_strcat(char *dest, const char *src);
char	*ft_strcpy(char *dest, const char *src);
void	*safe_malloc(size_t size);
bool	more_execution(int fd, char *buffer, size_t buffer_size);

/**
 * @brief  Build full path.
 *
 * This function builds the full path.
 *
 * @param dir The directory.
 * @param command The command.
 * @return A pointer to the full path.
 */
char	*build_full_path(const char *dir, const char *command)
{
	char	*full_path;

	full_path = safe_malloc(ft_strlen(dir) + ft_strlen(command) + 2);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, dir);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, command);
	return (full_path);
}

/**
 * @brief  Find the execution node.
 *
 * This function finds the execution node.
 *
 * @param cmd The command node.
 * @param is_pipe A pointer to the is_pipe flag.
 * @return A pointer to the execution node.
 */
t_ast_node	*find_execution_node(t_ast_node *cmd, int *is_pipe)
{
	while (cmd)
	{
		if (cmd->type == NODE_COMMAND)
			return (cmd);
		if (cmd->type == NODE_PIPE)
		{
			*is_pipe = 1;
			return (cmd);
		}
		if (cmd->type == NODE_REDIRECTION && cmd->data.redirection.child)
			cmd = cmd->data.redirection.child;
		else
			break ;
	}
	return (NULL);
}

/**
 * @brief  Find the output redirection.
 *
 * This function finds the output redirection.
 *
 * @param cmd_node The command node.
 * @return A pointer to the output redirection node.
 */
t_ast_node	*find_output_redirection(t_ast_node *cmd_node)
{
	t_ast_node	*output_redir;

	while (cmd_node && cmd_node->type == NODE_REDIRECTION)
	{
		if (cmd_node->data.redirection.type == REDIR_OUTPUT
			|| cmd_node->data.redirection.type == REDIR_APPEND)
		{
			output_redir = cmd_node;
			cmd_node->data.redirection.type = REDIR_NONE;
		}
		cmd_node = cmd_node->data.redirection.child;
	}
	return (output_redir);
}

/**
 * @brief Print File Descriptor
 *
 * @param fd File Descriptor
 */
void	print_fd(int fd)
{
	char		buffer[4096];
	ssize_t		bytes_read;

	if (fd < 0)
		return ;
	bytes_read = read(fd, buffer, sizeof(buffer));
	if (bytes_read < 0)
	{
		if (errno != EBADF)
			perror("read error");
		return ;
	}
	while (bytes_read > 0)
	{
		if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read)
			return (perror("write error"));
		bytes_read = read(fd, buffer, sizeof(buffer));
		if (bytes_read < 0)
		{
			if (errno != EBADF)
				perror("read error");
			return ;
		}
	}
}

/**
 * @brief Executes a command from a redirection node.
 * 
 * @param cmd Command AST node.
 * @param shell Shell state.
 * @param out_fd Output file descriptor to assign if needed.
 * @return int File descriptor from executed command.
 */
int	execute_from_cmd_node(t_ast_node *cmd, t_shell *shell, int out_fd)
{
	t_ast_node	*temp;
	int			fd;

	if (!cmd || cmd->type != NODE_COMMAND)
		return (STDIN_FILENO);
	if (out_fd != STDOUT_FILENO)
		cmd->fd_out = out_fd;
	temp = cmd;
	fd = execute_command(&temp, shell, 1);
	return (fd);
}
