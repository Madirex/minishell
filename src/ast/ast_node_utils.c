/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:08:54 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/05 18:04:43 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast/ast.h"
#include <unistd.h>
#include "utils/print.h"
/**
 * @file ast_node_utils.c
 * @brief Utility functions for managing AST nodes.
 */

char	*ft_strdup(const char *s);
void	safe_free(void **ptr);
void	*ft_memset(void *ptr, int value, size_t num);
void	*safe_malloc(size_t size);
void	ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief Allocates and initializes a new AST node of the given type.
 *
 * This function creates a new abstract syntax tree (AST) node and sets its type
 * to the specified value. The node is allocated on the heap and should be freed
 * by the caller when it is no longer needed.
 *
 * @param type The type of the node to be allocated.
 * @return A pointer to the newly allocated AST node, or NULL
 * if allocation fails.
 * 
 * @note The function initializes the node's environment pointer to NULL.
 * The node's data field is zeroed out using ft_memset.
 * 
 */
t_ast_node	*allocate_node(t_node_type type)
{
	t_ast_node	*node;

	node = (t_ast_node *)safe_malloc(sizeof(t_ast_node));
	if (!node)
	{
		handle_allocation_error(type);
		return (NULL);
	}
	node->type = type;
	node->env = NULL;
	node->next = NULL;
	node->fd_in = STDIN_FILENO;
	node->fd_out = STDOUT_FILENO;
	node->is_pipe = false;
	ft_memset(&node->data, 0, sizeof(t_node_data));
	if (type == NODE_COMMAND)
	{
		node->data.command.name = NULL;
		node->data.command.args = NULL;
	}
	return (node);
}

/**
 * @brief Appends a new node to the end of the linked list.
 *
 * This function takes a pointer to the head of a linked list and a new node,
 * and appends the new node to the end of the list. If the head is NULL, the
 * new node becomes the head of the list.
 *
 * @param head A double pointer to the head of the linked list.
 * @param new_node A pointer to the new node to be appended.
 * 
 * @note The function does nothing if the head or new node are NULL.
 */
void	append_node(t_ast_node **head, t_ast_node *new_node)
{
	t_ast_node	*current;

	if (!head || !new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
}
