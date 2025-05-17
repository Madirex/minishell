/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:43:13 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/24 18:43:52 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/str_utils.h"

void	*safe_malloc(size_t size);
size_t	ft_strlen(const char *s);

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*dup;
	char	*start;

	len = ft_strlen(s);
	if (n < len)
		len = n;
	dup = safe_malloc(len + 1);
	if (!dup)
		return (NULL);
	start = dup;
	while (*s && n--)
		*dup++ = *s++;
	*dup = '\0';
	return (start);
}

/**
 * @brief Computes the length of the string.
 *
 * This function takes a constant character pointer as input and returns the
 * length of the string, excluding the null terminator.
 *
 * @param s The input string whose length is to be computed.
 * @return The length of the string.
 */
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

/**
 * @brief Copies up to dstsize - 1 characters from the string src to dst,
 * NULL-terminating the result if dstsize is not 0.
 *
 * @param dst The destination buffer.
 * @param src The source string.
 * @param dstsize The size of the destination buffer.
 * @return The total length of the string it tried to create (length of src).
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (i < (dstsize - 1) && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}
