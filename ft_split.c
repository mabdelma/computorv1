/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelma <mabdelma@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 20:09:25 by mabdelma          #+#    #+#             */
/*   Updated: 2023/03/06 22:12:41 by mabdelma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	count_separators(const char *str, char c)
{
	size_t	count;
	size_t	index;
	size_t	st[2];

	count = 0;
	st[0] = SIZE_MAX;
	st[1] = 0;
	index = 0;
	while (str[index] != '\0')
	{
		if (st[0] == SIZE_MAX && str[index] != c)
			st[0] = index;
		if (str[index] != c)
			st[1] = index;
		index++;
	}
	while (st[0] < st[1] && st[0] != SIZE_MAX)
	{
		if (str[st[0]] == c && ++count)
			while (str[st[0]] == c)
				st[0]++;
		else
			st[0]++;
	}
	return (count);
}

static size_t	custom_strlen(char const *string, char c)
{
	size_t	length;

	length = 0;
	while (*string != '\0' && *string != c)
	{
		string++;
		length++;
	}
	return (length);
}

static char	**inner_alloc_failure_handler(char **result, size_t result_index)
{
	size_t	i;

	i = 0;
	while (i < result_index)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

static char	**fillup(char const *s, char c, char **result)
{
	size_t	result_index;
	size_t	s_index;

	result_index = 0;
	s_index = 0;
	while (s[s_index] != '\0')
	{
		while (s[s_index] == c)
			s_index++;
		if (s[s_index] == '\0')
			break ;
		result[result_index] = ft_substr(s, s_index,
				custom_strlen(&(s[s_index]), c));
		if (result[result_index] == NULL)
			return (inner_alloc_failure_handler(result, result_index));
		result_index++;
		s_index += custom_strlen(&(s[s_index]), c);
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (0);
	if (s[0] == '\0')
		result = ft_calloc(1, sizeof(char *));
	else
		result = ft_calloc(count_separators(s, c) + 2, sizeof(char *));
	if (result == NULL)
		return (NULL);
	result = fillup(s, c, result);
	return (result);
}
