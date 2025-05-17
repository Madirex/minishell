/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_ast_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:08:28 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/11 19:03:35 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils/debug_print_ast.h"

void	print_command_node(t_ast_node *node, int depth)
{
	int	i;

	print_indentation(depth);
	if (node->data.command.name)
		printf("Command name: %s\n", node->data.command.name);
	else
		printf("Command name: (NULL)\n");
	if (node->data.command.args)
	{
		i = 0;
		while (node->data.command.args[i])
		{
			print_indentation(depth);
			printf("Arg[%d]: %s\n", i, node->data.command.args[i]);
			i++;
		}
	}
	else
	{
		print_indentation(depth);
		printf("Arguments: (NULL)\n");
	}
}

void	print_redirection_node(t_ast_node *node, int depth)
{
	print_indentation(depth);
	printf("Redirection type: %s\n",
		print_redirection_type(&node->data.redirection.type));
	print_indentation(depth);
	if (node->data.redirection.file)
		printf("Redirection file: %s\n", node->data.redirection.file);
	else
		printf("Redirection file: NULL\n");
	if (node->data.redirection.child)
	{
		print_indentation(depth);
		printf("Redirection child:\n");
		print_ast_node(node->data.redirection.child, depth + 1);
	}
	else
	{
		print_indentation(depth + 1);
		printf("Redirection child is NULL\n");
	}
}
