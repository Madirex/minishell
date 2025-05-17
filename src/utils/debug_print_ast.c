/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_ast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:46:40 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/22 21:15:20 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ast(t_ast *ast);
void	print_command_node(t_ast_node *node, int depth);
void	print_pipe_node(t_ast_node *node, int depth);
void	print_redirection_node(t_ast_node *node, int depth);
void	print_subshell_node(t_ast_node *node, int depth);
void	print_indentation(int depth);

char	*get_node_type_name(t_node_type type)
{
	if (type == NODE_COMMAND)
		return ("Command");
	else if (type == NODE_PIPE)
		return ("Pipe");
	else if (type == NODE_REDIRECTION)
		return ("Redirection");
	else if (type == NODE_SUBSHELL)
		return ("Subshell");
	else
		return ("Unknown");
}

char	*print_redirection_type(t_redir_type *redirection)
{
	if (!redirection)
		return (NULL);
	if (*redirection == REDIR_INPUT)
		return ("<");
	if (*redirection == REDIR_OUTPUT)
		return (">");
	if (*redirection == REDIR_APPEND)
		return (">>");
	if (*redirection == REDIR_HEREDOC)
		return ("<<");
	if (*redirection == REDIR_NONE)
		return ("NONE");
	return ("UNDEFINED");
}

void	print_indentation(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
}

void	print_ast_node(t_ast_node *node, int depth)
{
	if (!node)
	{
		print_indentation(depth);
		printf("Node is NULL\n");
		return ;
	}
	print_indentation(depth);
	printf("Node type: %s\n", get_node_type_name(node->type));
	if (node->type == NODE_COMMAND)
		print_command_node(node, depth);
	else if (node->type == NODE_PIPE)
		print_pipe_node(node, depth);
	else if (node->type == NODE_REDIRECTION)
		print_redirection_node(node, depth);
	else if (node->type == NODE_SUBSHELL)
		print_subshell_node(node, depth);
	else
	{
		print_indentation(depth);
		printf("Unknown node type: %d\n", node->type);
	}
}

void	print_ast(t_ast *ast)
{
	printf("\n=========================\n");
	printf("=== AST DEBUG OUTPUT ===\n");
	if (!ast)
	{
		printf("AST is NULL\n");
		return ;
	}
	if (!ast->root)
	{
		printf("AST is empty\n");
		return ;
	}
	print_ast_node(ast->root, 0);
	printf("=========================\n\n");
}
