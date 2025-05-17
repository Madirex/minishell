/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_system.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:32:12 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/11 16:55:01 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file handle_system.c
 * @brief This file contains functions for handling system commands in the 
 * minishell project.
 *
 * It includes functions for executing commands, managing pipes, and handling 
 * errors during command execution. The functions in this file are responsible 
 * for interfacing with the operating system to execute user commands and manage
 * resources.
 */

#include "minishell.h"
#include "executor/executor.h"

int			create_pipe(int pipe_fd[2]);
char		*find_command_in_path(const char *command, t_env *env);
char		**env_to_array(t_env *env);
t_command	generate_full_command(t_ast_node *node);
pid_t		create_child_process(void);
int			cleanup_and_wait(pid_t pid, t_shell *shell,
				int fd_in, int pipe_read_end);
void		setup_child_io(int fd_in, int is_pipe,
				int pipe_fds[2], t_ast_node *node);
int			handle_pipe_and_wait(t_shell *shell, pid_t pid, t_pipe_data data);
char		*resolve_command_path(t_command command, t_shell *shell);
char		*handle_quotes(char *arg);
void		restore_signals(t_cmd_data cmd_data);
void		cleanup_resources(t_command command, int fd_in);

/**
 * @brief Handle errors during execve execution.
 *
 * This function is called when execve fails to execute the given command.
 * It cleans up allocated resources and prints an error message.
 *
 * @param envp The environment variables array.
 * @param args The command arguments array.
 * @param cmd_path Pointer to the command path string.
 * @param name The name of the command being executed.
 */
static void	handle_execve_error(char **envp, char **args,
							char **cmd_path, char *name)
{
	int	error_code;

	error_code = errno;
	if (error_code == EACCES)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(name, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		safe_free((void **)cmd_path);
		free_array(args);
		safe_free((void **)&name);
		free_array(envp);
		exit(126);
	}
	else
	{
		perror("execve");
		safe_free((void **)cmd_path);
		free_array(args);
		safe_free((void **)&name);
		free_array(envp);
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief Handle the case when a command is not found.
 *
 * This function prints an error message indicating that the command was not
 * found and cleans up allocated resources before exiting with a status code.
 *
 * @param command The command structure containing arguments and metadata.
 * @param envp The environment variables array.
 */
static void	command_not_found(t_command command, char **envp)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command.args[0], STDERR_FILENO);
	ft_putstr_fd(": command not found", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free_array(envp);
	free_array(command.args);
	safe_free((void **)&command.name);
	exit(127);
}

/**
 * @brief Processes all arguments of a command by handling quotes.
 *        Replaces original args if processed result is valid.
 * 
 * @param command The command whose args will be processed.
 */
void	process_command_args(t_command *command)
{
	int		i;
	char	*processed_arg;

	i = 0;
	while (command->args[i] != NULL)
	{
		processed_arg = handle_quotes(command->args[i]);
		if (processed_arg)
		{
			safe_free((void **)&command->args[i]);
			command->args[i] = processed_arg;
		}
		i++;
	}
}

/**
 * @brief Execute a system command.
 *
 * This function resolves the command path, prepares the environment, and
 * executes the command using execve. If the command is not found or cannot
 * be executed, it handles the error appropriately.
 *
 * @param command The command structure containing arguments and metadata.
 * @param shell The shell structure containing environment and state.
 */
static void	execute_sys_command(t_command command, t_shell *shell)
{
	char	**envp;
	char	*cmd_path;

	envp = env_to_array(shell->env);
	if (!envp)
	{
		perror("env allocation failed");
		exit(EXIT_FAILURE);
	}
	process_command_args(&command);
	cmd_path = resolve_command_path(command, shell);
	if (!cmd_path && (!command.args[0] || command.args[0][0] == '\0'))
	{
		free_array(envp);
		free_array(command.args);
		safe_free((void **)&command.name);
		exit(0);
	}
	if (!cmd_path)
		command_not_found(command, envp);
	execve(cmd_path, command.args, envp);
	handle_execve_error(envp, command.args, &cmd_path, command.name);
}

/**
 * @brief Handle the execution of a system command.
 *
 * This function manages the execution of a system command, including
 * setting up pipes, creating child processes, and cleaning up resources.
 *
 * @param node The AST node representing the command to execute.
 * @param shell The shell structure containing environment and state.
 * @param fd_in The file descriptor for input redirection.
 * @param is_pipe A flag indicating whether the command is part of a pipe.
 *
 * @return The file descriptor for the output of the command.
 */
int	handle_system_cmd(t_ast_node *node, t_shell *shell, int fd_in, int is_pipe)
{
	t_cmd_data	cmd_data;

	cmd_data.command = generate_full_command(node);
	cmd_data.data.fd_in = fd_in;
	cmd_data.data.is_pipe = is_pipe;
	if (is_pipe && create_pipe(cmd_data.data.pipe_fds) == -1)
		return (STDIN_FILENO);
	cmd_data.old_sigint = signal(SIGINT, SIG_IGN);
	cmd_data.old_sigquit = signal(SIGQUIT, SIG_IGN);
	cmd_data.pid = create_child_process();
	if (cmd_data.pid == -1)
		return (restore_signals(cmd_data), STDIN_FILENO);
	if (cmd_data.pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		setup_child_io(fd_in, is_pipe, cmd_data.data.pipe_fds, node);
		execute_sys_command(cmd_data.command, shell);
	}
	cmd_data.ret = handle_pipe_and_wait(shell, cmd_data.pid, cmd_data.data);
	restore_signals(cmd_data);
	return (cleanup_resources(cmd_data.command, fd_in), cmd_data.ret);
}
