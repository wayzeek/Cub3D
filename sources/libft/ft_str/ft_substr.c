/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:39:34 by jprofit           #+#    #+#             */
/*   Updated: 2022/12/12 13:51:52 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start >= (unsigned int)ft_strlen(s))
	{
		sub = ft_calloc(1, sizeof(*sub));
		if (sub == NULL)
			return (NULL);
		return (sub);
	}
	sub = malloc(sizeof(*sub) * (len + 1));
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (s[start] && len > 0)
	{
		sub[i++] = s[start++];
		len--;
	}
	sub[i] = '\0';
	return (sub);
}
