/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_ext2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:00:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/13 19:22:36 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/str_utils_ext.h"

void	*safe_malloc(size_t size);

/**
 * @brief Concatenates two strings.
 * 
 * This function concatenates two strings and returns the result.
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * @return A pointer to the concatenated string.
 */
char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = safe_malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2 + 1);
	result[len1 + len2] = '\0';
	return (result);
}

/** 
 * @brief Copies a string.
 * 
 * This function copies a string.
 * 
 * @param dest The destination string.
 * @param src The source string.
 * @return A pointer to the destination string.
 */
char	*ft_strcat(char *dest, const char *src)
{
	char	*d;

	d = dest;
	while (*d)
		d++;
	while (*src)
	{
		*d = *src;
		d++;
		src++;
	}
	*d = '\0';
	return (dest);
}
