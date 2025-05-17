/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_ext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:00:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/01/08 11:14:25 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/str_utils_ext.h"

/**
 * @file str_utils_ext.c
 * @brief Extended String Utilities
 * 
 * This file contains additional string utility functions that are used
 * throughout the minishell program.
 * 
 * The functions in this file provide additional functionality for string
 * manipulation, such as tokenizing strings, searching for characters,
 * and copying strings with a specified limit.
 * 
 */

/**
 * @brief Tokenizes a string into a sequence of tokens.
 *
 * This function is a reentrant version of strtok. It splits the string `str`
 * into tokens separated by characters in `delim`. The `saveptr` argument is
 * used to store the position of the next token between calls.
 *
 * @param str The string to be tokenized. If NULL, the function continues
 *            tokenizing the string from the last position stored in `saveptr`.
 * @param delim A string containing delimiter characters.
 * @param saveptr A pointer to a char pointer that stores the position of the
 * next token.
 * @return A pointer to the next token, or NULL if there are no more tokens.
 */
char	*ft_strtok_r(char *str, const char *delim, char **saveptr)
{
	char	*end;
	char	*token_start;

	if (!delim || !saveptr)
		return (NULL);
	if (str)
		*saveptr = str;
	if (!*saveptr)
		return (NULL);
	*saveptr = skip_delimiters(*saveptr, delim);
	if (!**saveptr)
		return (NULL);
	token_start = *saveptr;
	end = token_start;
	while (*end && !is_delimiter(*end, delim))
		end++;
	if (*end)
	{
		*end = '\0';
		*saveptr = end + 1;
	}
	else
		*saveptr = end;
	return (token_start);
}

/**
 * @brief Locate the first occurrence of a character in a string.
 *
 * This function searches for the first occurrence of the character `c`
 * (converted to a char) in the string pointed to by `str`. The terminating
 * null character is considered part of the string, so that if `c` is `\0`,
 * the function locates the terminating `\0`.
 *
 * @param str Pointer to the null-terminated string to be scanned.
 * @param c Character to be located. It is passed as an int, but it is
 * converted to a char.
 * @return A pointer to the first occurrence of the character `c` in the
 * string, or NULL if the character is not found.
 */
char	*ft_strchr(const char *str, int c)
{
	if (str == NULL)
		return (NULL);
	while (*str != '\0')
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return (NULL);
}

/**
 * @brief Copies a string from source to destination with a specified limit.
 *
 * This function copies up to n-1 characters from the source string
 * to the destination string and ensures that the destination string
 * is null-terminated.
 *
 * @param dest Pointer to the dest. buffer where content will be copied.
 * @param src Pointer to the source string to be copied.
 * @param n Max. num. of chars. to be copied from src, including null.
 */
void	ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == NULL || src == NULL)
		return ;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

/**
* @brief Skips delimiters in a string.
*
* This function skips delimiters in a string until a non-delimiter character
* is found.
*
* @param str The string to be scanned.
* @param delim A string containing delimiter characters.
* @return A pointer to the first non-delimiter character in the string.
*/
char	*skip_delimiters(char *str, const char *delim)
{
	while (*str && is_delimiter(*str, delim))
		str++;
	return (str);
}

/**
 * @brief Appends the src string to the dst string, ensuring that the result is
 *        null-terminated and does not exceed dstsize - 1 characters.
 *
 * @param dst The destination buffer.
 * @param src The source string.
 * @param dstsize The size of the destination buffer.
 * @return The total length of the string it tried to create (initial 
 * length of dst + length of src).
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	dst_len = 0;
	while (dst_len < dstsize && dst[dst_len] != '\0')
		dst_len++;
	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (dst_len == dstsize)
		return (dstsize + src_len);
	i = dst_len;
	j = 0;
	while (i < (dstsize - 1) && src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst_len + src_len);
}
