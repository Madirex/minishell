/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:37:46 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/01/08 10:32:54 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ast_node_error.c
 * 
 * This file contains functions for handling memory allocation errors
 * for different types of AST nodes.
 * 
 */

#include "ast/ast.h"
#include "utils/print.h"

void	ft_error_msg(const char *prefix, const char *msg);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
void	ft_memset(void *b, int c, size_t len);

/**
 * @brief Handles memory allocation errors for AST nodes.
 *
 * This function prints an error message to the standard error stream
 * when memory allocation fails for different types of AST nodes.
 *
 * @param type The type of AST node for which allocation failed.
 * 
 * @note The function uses the ft_error_msg function to print the error message.
 * 
 */
void	handle_allocation_error(t_node_type type)
{
	const char	*type_str;
	char		error_msg[100];

	ft_memset(error_msg, 0, sizeof(error_msg));
	if (type == NODE_COMMAND)
		type_str = "COMMAND";
	else if (type == NODE_PIPE)
		type_str = "PIPE";
	else if (type == NODE_REDIRECTION)
		type_str = "REDIRECTION";
	else if (type == NODE_SUBSHELL)
		type_str = "SUBSHELL";
	else
		type_str = "UNKNOWN";
	ft_strlcpy(error_msg, "Failed to allocate memory for ",
		sizeof(error_msg));
	ft_strlcat(error_msg, type_str, sizeof(error_msg));
	ft_strlcat(error_msg, " node", sizeof(error_msg));
	ft_error_msg(AST_ERR, error_msg);
}
