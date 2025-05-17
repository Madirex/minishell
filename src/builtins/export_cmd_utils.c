/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd_utils.c.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:53:19 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/04 18:59:21 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/export_cmd.h"

void	*safe_malloc(size_t size);
int		get_fd_from_str(void *str);

static bool	is_valid_identifier_start(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (true);
	return (false);
}

static bool	is_valid_identifier_char(char c)
{
	if (is_valid_identifier_start(c) || (c >= '0' && c <= '9'))
		return (true);
	return (false);
}

bool	is_valid_export_arg(const char *arg)
{
	int	i;

	i = 0;
	if (!arg || !arg[0])
		return (false);
	if (!is_valid_identifier_start(arg[0]))
		return (false);
	while (arg[i] && arg[i] != '=')
	{
		if (!is_valid_identifier_char(arg[i]))
			return (false);
		i++;
	}
	return (true);
}
