/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:57:04 by ozdemir           #+#    #+#             */
/*   Updated: 2024/12/05 17:05:32 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	is_a_sep(char const *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*aft_strtrim(char const *s1, char const *set, t_arena *arena)
{
	size_t	size;
	char	*dest;
	size_t	i;

	if (!s1)
		return (NULL);
	size = 0;
	while (is_a_sep(set, *s1))
		s1++;
	while (*s1++)
		size++;
	while (size > 0 && is_a_sep(set, *(s1 - 2)))
	{
		size--;
		s1--;
	}
	dest = arena_alloc(arena, sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < (size))
		dest[i++] = *(s1++ - (size + 1));
	dest[i] = 0;
	return (dest);
}

char	*aft_strdup(const char *src, t_arena *arena)
{
	char	*dest;
	int		i;

	if (!src)
		return (NULL);
	dest = arena_alloc(arena ,ft_strlen(src) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*aft_strndup(char *str, unsigned int n, t_arena *arena)
{
	char			*dest;
	unsigned int	i;

	i = 0;
        if (n == 0)
                return ("");
	dest = arena_alloc(arena, sizeof(char) * (n + 1));
	if (!dest)
		return (NULL);
	while (i < n)
	{
		dest[i] = *str;
		i++;
		str++;
	}
	dest[n] = 0;
	return (dest);
}

char	*aft_substr(char const *s, unsigned int start, size_t len, t_arena *arena)
{
	char	*sub_str;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (aft_strdup("", arena));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	sub_str = arena_alloc(arena, (len + 1) * sizeof(char));
	if (!sub_str)
		return (NULL);
	ft_strlcpy(sub_str, s + start, len + 1);
	return (sub_str);
}

char	*aft_strjoin(char const *s1, char const *s2, t_arena *arena)
{
	char	*dest;
	size_t	total_len;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	dest = arena_alloc(arena, sizeof(char) * (total_len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (*s1)
	{
		dest[i++] = *s1++;
	}
	while (*s2)
	{
		dest[i++] = *s2++;
	}
	dest[i] = '\0';
	return (dest);
}
