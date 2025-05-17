/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:15:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 18:54:08 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "types.h"

# include <fcntl.h>
# include <sys/wait.h>

# ifndef EXEC_BUFFER_SIZE 
#  define EXEC_BUFFER_SIZE 4096
# endif

typedef struct s_pipe_data
{
	int	fd_in;
	int	pipe_fds[2];
	int	is_pipe;
}	t_pipe_data;

typedef struct s_cmd_data
{
	t_command	command;
	t_pipe_data	data;
	pid_t		pid;
	int			ret;
	void		(*old_sigint)(int);
	void		(*old_sigquit)(int);
}	t_cmd_data;

typedef struct s_cmd_context
{
	t_ast_node	*cmd;
	t_ast_node	*right_node;
	int			last_input_fd;
	int			left_fd;
}	t_cmd_context;

typedef struct s_more_data
{
	int		pipe_fd[2];
	pid_t	pid;
	ssize_t	bytes_read;
	char	*args[2];
	char	*envp[1];
}			t_more_data;

void		execute_ast(t_ast *ast, t_shell *shell);
int			process_redirection(t_ast_node *node_cpy, t_shell *shell);
int			handle_node_command(t_ast_node *node_cpy, t_shell *shell,
				int *is_pipe);
int			execute_command(t_ast_node **node, t_shell *shell, int is_pipe);
int			handle_system_cmd(t_ast_node *node, t_shell *shell, int fd_in,
				int is_pipe);
int			handle_pipe_and_wait(t_shell *shell, pid_t pid, t_pipe_data data);
int			cleanup_and_wait(pid_t pid, t_shell *shell, int fd_in,
				int pipe_read_end);
char		*find_command_in_path(const char *command, t_env *env);
t_ast_node	*find_execution_node(t_ast_node *cmd, int *is_pipe);
t_ast_node	*find_output_redirection(t_ast_node *cmd_node);
t_command	generate_full_command(t_ast_node *node);
void		setup_child_io(int fd_in, int is_pipe,
				int pipe_fds[2], t_ast_node *node);
pid_t		create_child_process(void);
int			create_pipe(int pipe_fd[2]);
char		*resolve_command_path(t_command command, t_shell *shell);
int			handle_pipe_node(t_ast_node *node, t_shell *shell);
int			process_pipe_right(t_ast_node *right_node, int left_fd,
				t_shell *shell, int is_pipe);
t_ast_node	*process_right_redir_input(t_ast_node *current, t_shell *shell,
				int *last_input_fd);
int			process_right_redirection_output(t_ast_node *right_node,
				int cmd_fd, int is_pipe);
int			process_pipe_right_redirection(t_ast_node *right_node,
				int left_fd, t_shell *shell, int is_pipe);
t_ast_node	*find_cmd_node(t_ast_node *current);
int			handle_input_redirection(t_ast_node *current, t_shell *shell,
				int *last_input_fd);
void		preserve_command_exit_status(t_shell *shell, int status);
int			handle_output_redirection(t_ast_node *current,
				t_ast_node **last_output);
int			execute_cmd_with_redirections(t_ast_node *cmd_node,
				t_ast_node *last_output, int last_input_fd, t_shell *shell);
int			handle_command_node(t_ast_node *node, t_shell *shell, int is_pipe);
int			handle_redirection_node(t_ast_node *node, t_shell *shell);
bool		more_execution(int fd, char *buffer, size_t buffer_size);
bool		is_more_last_command(t_ast_node *node);

#endif
