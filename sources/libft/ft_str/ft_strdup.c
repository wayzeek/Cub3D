/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:53:29 by jprofit           #+#    #+#             */
/*   Updated: 2022/12/12 13:53:05 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	size_t	len;

	len = ft_strlen(s1);
	cpy = malloc(sizeof(*cpy) * (len + 1));
	if (cpy == NULL)
		return (NULL);
	ft_strlcpy(cpy, s1, len + 1);
	return (cpy);
}
