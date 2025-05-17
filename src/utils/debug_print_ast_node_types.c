/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_ast_node_types.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:00:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/11 19:03:47 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils/debug_print_ast.h"

void	print_pipe_node(t_ast_node *node, int depth)
{
	print_indentation(depth);
	printf("PIPE:\n");
	print_indentation(depth);
	printf("Left:\n");
	if (node->data.pipe.left)
		print_ast_node(node->data.pipe.left, depth + 1);
	else
	{
		print_indentation(depth + 1);
		printf("Left pipe is NULL\n");
	}
	print_indentation(depth);
	printf("Right:\n");
	if (node->data.pipe.right)
		print_ast_node(node->data.pipe.right, depth + 1);
	else
	{
		print_indentation(depth + 1);
		printf("Right pipe is NULL\n");
	}
}

void	print_subshell_node(t_ast_node *node, int depth)
{
	print_indentation(depth);
	printf("Subshell:\n");
	if (node->data.subshell.child)
		print_ast_node(node->data.subshell.child, depth + 1);
	else
	{
		print_indentation(depth + 1);
		printf("Subshell child is NULL\n");
	}
}
