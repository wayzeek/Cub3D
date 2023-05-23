/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:40:54 by jprofit           #+#    #+#             */
/*   Updated: 2022/12/12 13:53:26 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ischarset(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	skipfrontset(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (ischarset(s1[i], set))
		i++;
	return (i);
}

static size_t	skipbackset(char const *s1, char const *set)
{
	size_t	i;

	i = ft_strlen(s1);
	if (i == 0)
		return (i);
	while (i > 0)
	{
		i--;
		if (!ischarset(s1[i], set))
			break ;
	}
	return ((size_t)i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	start;
	size_t	j;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	start = skipfrontset(s1, set);
	end = skipbackset(s1, set);
	if (start > end)
		return (ft_strdup(""));
	res = malloc(sizeof(*res) * (end - start + 1));
	if (res == 0)
		return (NULL);
	j = 0;
	while (start < end)
	{
		res[j++] = s1[start++];
	}
	res[j] = '\0';
	return (res);
}
