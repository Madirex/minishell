/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:38:12 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 18:54:08 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor.c
 * @brief This file contains the implementation of the command execution
 * functions for the shell.
 * 
 * This file includes functions for executing commands, handling pipes,
 * managing redirections, and waiting for child processes.
 * It also includes functions for handling built-in commands and
 * executing external commands.
 * The main function is execute_ast, which takes an abstract syntax tree
 * and a shell structure as arguments and executes the commands in the tree.
 */

#include "minishell.h"
#include "executor/executor.h"

int		execute_command(t_ast_node **node, t_shell *shell, int is_pipe);
void	print_ast(t_ast *ast);
void	print_fd(int fd);
int		handle_system_cmd(t_ast_node *node,
			t_shell *shell, int fd_in, int is_pipe);
int		handle_node_command(t_ast_node *node_cpy, t_shell *shell, int *is_pipe);

/**
 * @brief Wait for all child processes to finish
 * 
 * @param shell Shell struct
 * @return void
 */
static void	wait_for_processes(t_shell *shell)
{
	int		status;
	pid_t	pid;

	pid = waitpid(-1, &status, WNOHANG);
	while (pid > 0)
	{
		preserve_command_exit_status(shell, status);
		pid = waitpid(-1, &status, WNOHANG);
	}
}

/**
 * @brief Wait for all child processes to finish and return the last status
 * 
 * @param void
 * @return int The last status of the child processes
 */
static int	wait_for_children(void)
{
	int	status;
	int	last_status;

	last_status = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_status = 128 + WTERMSIG(status);
	}
	return (last_status);
}

/**
 * @brief Execute a single command and handle its output
 *
 * @param current Current AST node
 * @param shell Shell struct
 * @return Whether the command was handled
 */
static int	execute_single_command(t_ast_node **current, t_shell *shell)
{
	int		original_stdout;
	int		original_term;
	int		final_fd;
	bool	is_more;
	char	local_buffer[EXEC_BUFFER_SIZE];

	original_stdout = dup(STDOUT_FILENO);
	original_term = isatty(STDOUT_FILENO);
	is_more = is_more_last_command(*current);
	final_fd = execute_command(current, shell, 0);
	if (original_stdout > 2)
	{
		if (original_term)
			dup2(original_stdout, STDOUT_FILENO);
		close(original_stdout);
	}
	if (final_fd != -1)
	{
		if (is_more)
			more_execution(final_fd, local_buffer, sizeof(local_buffer));
		else
			print_fd(final_fd);
	}
	wait_for_processes(shell);
	return (1);
}

/**
 * @brief Handle execution of commands in the AST
 *
 * @param current Current AST node
 * @param shell Shell struct
 */
static void	handle_command_execution(t_ast_node *current, t_shell *shell)
{
	unsigned int	command_handled;

	command_handled = 0;
	while (current)
	{
		if (!command_handled)
			command_handled = execute_single_command(&current, shell);
		else if (current->type != NODE_COMMAND)
			command_handled = 0;
		current = current->next;
	}
}

/**
 * @brief Execute command
 * 
 * @param ast the ast
 * @param shell the shell struct
 */
void	execute_ast(t_ast *ast, t_shell *shell)
{
	int		final_fd;
	bool	is_more;
	char	local_buffer[EXEC_BUFFER_SIZE];

	if (!ast || !ast->root)
		return ;
	if (ast->root->type == NODE_PIPE)
	{
		is_more = is_more_last_command(ast->root);
		final_fd = execute_command(&ast->root, shell, 1);
		if (final_fd != -1)
		{
			if (is_more)
				more_execution(final_fd, local_buffer, sizeof(local_buffer));
			else
				print_fd(final_fd);
		}
		shell->exit_status = wait_for_children();
	}
	else
		handle_command_execution(ast->root, shell);
}
