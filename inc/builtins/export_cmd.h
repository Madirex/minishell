/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:42:17 by anmateo-          #+#    #+#             */
/*   Updated: 2025/04/21 16:19:53 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file export_cmd.h
 * @brief Export command header file.
 *
 * This file contains the declarations of functions and structures used for
 * handling the export command in a shell environment.
 */

#ifndef EXPORT_CMD_H
# define EXPORT_CMD_H

# include "env/env.h"
# include "utils/str_utils.h"
# include <stdio.h>

char	*handle_quotes(char *arg);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
bool	is_valid_export_arg(const char *arg);
char	*get_export_res(t_env *env);
char	*extract_var_name(const char *str, char **value);
void	handle_export_output(t_ast_node *node, char *export_result);
void	print_export_error(char *arg, t_shell *shell);
char	*process_export_value(char *value);
void	update_environment(t_ast_node *node, t_shell *shell,
			char *var_name, char *value);

#endif
