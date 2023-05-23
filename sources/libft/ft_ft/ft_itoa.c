/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:46:40 by jprofit           #+#    #+#             */
/*   Updated: 2022/12/12 13:51:44 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	lenint(int n)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	inttochar(char *res, long n, size_t len)
{
	res[len] = '\0';
	len--;
	while (n > 0)
	{
		res[len] = n % 10 + '0';
		n /= 10;
		len--;
	}
}

static char	*exept_minzero(long n)
{
	if (n == 0)
		return (ft_strdup("0"));
	return (ft_strdup("-2147483648"));
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*res;

	if (n == -2147483648 || n == 0)
		return (exept_minzero(n));
	len = lenint(n);
	res = malloc(sizeof(*res) * (len + 1));
	if (!res)
		return (NULL);
	if (n < 0)
	{
		res[0] = '-';
		inttochar(res, -n, len);
	}
	else
		inttochar(res, n, len);
	return (res);
}
