/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd_utils_ext.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:00:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/13 18:11:53 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/export_cmd.h"
#include "minishell.h"

void	*safe_malloc(size_t size);
int		get_fd_from_str(void *str);

/**
 * @brief Handles writing export result to file descriptor or creating a 
 * string FD
 * 
 * @param node AST node representing the export command
 * @param export_result The export result string
 */
void	handle_export_output(t_ast_node *node, char *export_result)
{
	if (!export_result)
		return ;
	if (node->fd_out != STDOUT_FILENO)
	{
		write(node->fd_out, export_result, ft_strlen(export_result));
		safe_free((void **)&export_result);
		return ;
	}
	node->fd_in = get_fd_from_str(export_result);
	safe_free((void **)&export_result);
}

/**
 * @brief Prints error for invalid export argument
 * 
 * @param arg The invalid argument
 * @param shell The shell context to update exit status
 */
void	print_export_error(char *arg, t_shell *shell)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	shell->exit_status = 1;
}

/**
 * @brief Process the value for export
 * 
 * @param value The value to process
 * @return char* The processed value
 */
char	*process_export_value(char *value)
{
	char	*quoted_value;

	if (!value)
		return (NULL);
	quoted_value = handle_quotes(value);
	safe_free((void **)&value);
	return (quoted_value);
}

/**
 * @brief Updates environment with new variable
 * 
 * @param node The AST node
 * @param shell The shell context
 * @param var_name The variable name
 * @param value The variable value
 */
void	update_environment(t_ast_node *node, t_shell *shell,
						char *var_name, char *value)
{
	if (node->is_pipe)
		return ;
	if (var_name && value)
		env_append_node(&shell->env, var_name, value);
	else if (var_name)
		env_create_empty_node(shell->env, var_name);
}
