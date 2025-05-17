/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:21:45 by anmateo-          #+#    #+#             */
/*   Updated: 2025/04/13 18:11:42 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/export_cmd.h"

void	*safe_malloc(size_t size);
int		get_fd_from_str(void *str);

/**
 * @brief Helper function to append the formatted environment variable to 
 * the result
 * 
 * @param res The string to append to
 * @param cur The current environment variable
 * @param len The maximum length of the string
 */
static void	append_env_var_to_result(char *res, t_env *cur, size_t len)
{
	ft_strlcat(res, "declare -x ", len);
	ft_strlcat(res, cur->key, len);
	if (cur->value)
	{
		ft_strlcat(res, "='", len);
		ft_strlcat(res, cur->value, len);
		ft_strlcat(res, "'", len);
	}
	ft_strlcat(res, "\n", len);
}

/**
 * @brief Get export response
 * 
 * This function prints the export command, which lists all environment variables
 * in the shell's environment.
 *
 * @param env A pointer to the environment structure containing
 * environment variables.
 * @return A string containing all environment variables.
 */
char	*get_export_res(t_env *env)
{
	t_env	*cur;
	size_t	len;
	char	*res;

	cur = env;
	len = 1;
	while (cur)
	{
		len += ft_strlen("declare -x ") + ft_strlen(cur->key) + 2;
		if (cur->value)
			len += ft_strlen(cur->value) + 3;
		cur = cur->next;
	}
	res = safe_malloc(len);
	if (!res)
		return (NULL);
	res[0] = '\0';
	cur = env;
	while (cur)
	{
		append_env_var_to_result(res, cur, len);
		cur = cur->next;
	}
	return (res);
}

/**
 * @brief Extracts the variable name from a string.
 *
 * This function extracts the variable name from a string containing
 * an environment variable in the format "key=value
 *
 * @param str The string to extract the variable name from.
 * @param value A pointer to the value of the environment variable.
 * @return A pointer to the extracted variable name.
 */
char	*extract_var_name(const char *str, char **value)
{
	int		i;
	char	*var_name;

	i = 0;
	var_name = NULL;
	while (str[i])
	{
		if (str[i] == '=')
		{
			var_name = ft_strdup(str);
			if (!var_name)
				return (NULL);
			var_name[i] = '\0';
			*value = ft_strdup(str + i + 1);
			if (!*value)
			{
				safe_free((void **)&var_name);
				return (NULL);
			}
			break ;
		}
		i++;
	}
	return (var_name);
}

/** 
 * @brief Handles the export command for the minishell.
 * 
 * This function processes the export command, setting or
 * updating the value of an environment variable in the
 * shell's environment.
 * 
 * @param node A pointer to the AST node representing the export command.
 * @param shell A pointer to the environment structure.
 */
void	handle_export(t_ast_node *node, t_shell *shell)
{
	char	*var_name;
	char	*value;
	char	**args;

	var_name = NULL;
	value = NULL;
	args = node->data.command.args;
	if (!args[1])
	{
		handle_export_output(node, get_export_res(shell->env));
		return ;
	}
	if (!is_valid_export_arg(args[1]))
	{
		print_export_error(args[1], shell);
		return ;
	}
	var_name = extract_var_name(args[1], &value);
	value = process_export_value(value);
	update_environment(node, shell, var_name, value);
	safe_free((void **)&var_name);
	safe_free((void **)&value);
}
