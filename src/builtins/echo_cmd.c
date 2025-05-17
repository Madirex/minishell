/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:21:25 by anmateo-          #+#    #+#             */
/*   Updated: 2025/04/13 19:23:23 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/echo_cmd.h"

char	*handle_quotes(char *arg);
char	*create_empty_echo(void);
void	handle_echo_output(t_ast_node *node, char *str);
char	*prepare_echo_string(char *processed, int new_line);
void	write_echo_output(int fd, char *str);
void	*safe_malloc(size_t size);
char	*ft_strcat(char *dest, const char *src);
char	*expand_home(char *arg, t_env *env);

/** 
 * @brief Handles the echo command flags.
 * 
 * This function processes the flags for the echo command.
 * 
 * @param args An array of strings representing the arguments passed
 * to the echo command.
 * @param arg_num A pointer to the current argument number.
 * @param new_line A pointer to the new line flag.
 */
void	handle_echo_flags(char **args, int *arg_num, int *new_line)
{
	bool	try_next;

	try_next = 1;
	if (try_next)
	{
		try_next = 0;
		if (args[*arg_num] && args[*arg_num][0] && args[*arg_num][0] == '-')
		{
			if (args[*arg_num][1] && args[*arg_num][1] == 'n')
			{
				if (!args[*arg_num][2] || (args[*arg_num][2]
					&& args[*arg_num][2] == ' '))
				{
					(*arg_num)++;
					*new_line = 0;
					try_next = 1;
				}
			}
		}
	}
}

/**
 * @brief Concatenates a single argument with the current result
 * 
 * @param result Current concatenated string
 * @param arg Argument to concatenate
 * @param add_space Whether to add a space after the argument
 * @param env Environment variables for tilde expansion
 * @return Updated concatenated string or NULL on error
 */
static char	*concat_single_arg(char *result, char *arg, int add_space,
	t_env *env)
{
	char	*temp;
	char	*expanded;
	char	*new_result;

	expanded = expand_home(arg, env);
	if (!expanded)
		return (NULL);
	temp = result;
	new_result = safe_malloc(ft_strlen(temp) + ft_strlen(expanded) + 1
			+ add_space);
	if (!new_result)
		return (NULL);
	ft_strcpy(new_result, temp);
	ft_strcat(new_result, expanded);
	if (add_space)
		ft_strcat(new_result, " ");
	safe_free((void **)&temp);
	safe_free((void **)&expanded);
	return (new_result);
}

/** 
 * @brief Concatenates the arguments passed to the echo command.
 * 
 * This function concatenates the arguments passed to the echo command.
 * 
 * @param args An array of strings representing the arguments passed
 * to the echo command.
 * @param env The environment variables list.
 * @return A pointer to the concatenated string.
 */
static char	*concat_args(char **args, int start_index, t_env *env)
{
	char	*result;
	int		i;
	int		add_space;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = start_index;
	while (args[i])
	{
		add_space = (args[i + 1] != NULL);
		result = concat_single_arg(result, args[i], add_space, env);
		if (!result)
			return (NULL);
		i++;
	}
	return (result);
}

/**
 * @brief Process echo command arguments
 * 
 * @param args Command arguments
 * @param env Environment variables
 * @param new_line Newline flag
 * @return Processed string ready for output
 */
static char	*process_echo_args(char **args, t_env *env,
					int arg_num, int new_line)
{
	char	*concatenated;
	char	*processed;
	char	*str;

	concatenated = concat_args(args, arg_num, env);
	if (!concatenated)
		return (NULL);
	processed = handle_quotes(concatenated);
	safe_free((void **)&concatenated);
	str = prepare_echo_string(processed, new_line);
	safe_free((void **)&processed);
	return (str);
}

/** 
 * @brief Executes the echo command.
 * 
 * This function executes the echo command, which
 * prints the arguments passed to it.
 * 
 * @param node A pointer to the AST node representing the echo command.
 * @param shell A pointer to the shell structure.
 */
void	handle_echo(t_ast_node *node, t_shell *shell)
{
	int		arg_num;
	int		new_line;
	char	**args;
	char	*str;

	arg_num = 1;
	new_line = 1;
	args = node->data.command.args;
	if (!args || !args[0])
	{
		str = create_empty_echo();
		handle_echo_output(node, str);
		return ;
	}
	handle_echo_flags(args, &arg_num, &new_line);
	str = process_echo_args(args, shell->env, arg_num, new_line);
	if (str)
		handle_echo_output(node, str);
}
