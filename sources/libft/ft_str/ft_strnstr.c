/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:21:52 by jprofit           #+#    #+#             */
/*   Updated: 2022/12/12 13:53:21 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	temp;

	if (needle[0] == '\0')
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	i = 0;
	while (haystack[i] != '\0' && len > 0)
	{
		j = 0;
		temp = len;
		while (haystack[i + j] == needle [j] && temp > 0)
		{
			if (needle[j + 1] == '\0')
				return ((char *)haystack + i);
			j++;
			temp--;
		}
		i++;
		len--;
	}
	return (NULL);
}
