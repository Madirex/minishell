/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:18:25 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/13 19:23:16 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/echo_cmd.h"

void	*safe_malloc(size_t size);
char	*ft_strcat(char *dest, const char *src);
int		get_fd_from_str(void *str);
char	*ft_strcat(char *dest, const char *src);

/**
 * @brief Expands tildes to the home directory using the t_env list.
 * 
 * @param arg The argument to process.
 * @param env The linked list of environment variables.
 * @return A pointer to the string with the expanded tilde.
 */
char	*expand_home(char *arg, t_env *env)
{
	char	*home;
	char	*expanded;

	if (arg[0] == '~' && (arg[1] == '\0' || arg[1] == '/'))
	{
		home = get_env_value("HOME", env);
		if (!home)
			return (ft_strdup(arg));
		expanded = safe_malloc(ft_strlen(home) + ft_strlen(arg));
		if (!expanded)
			return (NULL);
		ft_strcpy(expanded, home);
		ft_strcat(expanded, arg + 1);
		return (expanded);
	}
	return (ft_strdup(arg));
}

/**
 * @brief Writes echo output to file descriptor
 * 
 * @param fd The file descriptor to write to
 * @param str The string to write
 */
void	write_echo_output(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
}

/**
 * @brief Creates an empty echo string with newline
 * 
 * @return char* The empty echo string
 */
char	*create_empty_echo(void)
{
	char	*str;

	str = safe_malloc(2);
	str[0] = '\n';
	str[1] = '\0';
	return (str);
}

/**
 * @brief Prepares the echo string with or without newline
 * 
 * @param processed The processed input string
 * @param new_line Flag for newline
 * @return char* The final echo string
 */
char	*prepare_echo_string(char *processed, int new_line)
{
	char	*str;

	str = NULL;
	if (processed)
	{
		str = safe_malloc(ft_strlen(processed) + 1 + new_line);
		ft_strcpy(str, processed);
		if (new_line)
			ft_strcat(str, "\n");
	}
	return (str);
}

/**
 * @brief Handles echo command output
 * 
 * @param node The AST node 
 * @param str The string to output
 */
void	handle_echo_output(t_ast_node *node, char *str)
{
	if (node->fd_out != STDOUT_FILENO)
	{
		write_echo_output(node->fd_out, str);
		safe_free((void **)&str);
		return ;
	}
	node->fd_in = get_fd_from_str(str);
	safe_free((void **)&str);
}
