/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:21:53 by anmateo-          #+#    #+#             */
/*   Updated: 2025/04/04 18:34:12 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/pwd_cmd.h"

void	*safe_malloc(size_t size);
int		get_fd_from_str(void *str);

/**
 * @brief Gets the current working directory.
 *
 * This function gets the current working directory of the shell.
 *
 * @return A pointer to a string containing the current working directory.
 */
char	*get_current_directory(void)
{
	size_t	size;
	char	*buffer;

	size = 1024;
	buffer = (char *)safe_malloc(size);
	if (!buffer)
	{
		write(2, "Error: safe_malloc failed\n", 21);
		return (NULL);
	}
	if (!getcwd(buffer, size))
	{
		write(2, "Error: getcwd failed\n", 21);
		safe_free((void **)&buffer);
		return (NULL);
	}
	return (buffer);
}

/**
 * @brief Executes the pwd command.
 * 
 * This function executes the pwd command,
 * which prints the current working directory
 * of the shell.
 * 
 * @param node A pointer to the AST node representing the pwd command.
 */
void	handle_pwd(t_ast_node *node)
{
	char	*cwd;
	char	*str;

	cwd = get_current_directory();
	if (!cwd)
		return ;
	str = safe_malloc(ft_strlen(cwd) + 2);
	if (!str)
	{
		safe_free((void **)&cwd);
		return ;
	}
	str = ft_strcpy(str, cwd);
	str = ft_strcat(str, "\n");
	if (node->fd_out != STDOUT_FILENO)
	{
		write(node->fd_out, str, ft_strlen(str));
		safe_free((void **)&str);
		safe_free((void **)&cwd);
		return ;
	}
	node->fd_in = get_fd_from_str(str);
	safe_free((void **)&str);
	safe_free((void **)&cwd);
}
