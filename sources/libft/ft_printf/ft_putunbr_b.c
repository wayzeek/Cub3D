/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 15:11:52 by jprofit           #+#    #+#             */
/*   Updated: 2022/12/12 13:58:40 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

ssize_t	ft_putunbr_b(unsigned long nb, char *base, ssize_t *len)
{
	size_t		blen;

	blen = ft_strlen(base);
	if (nb < blen && *len != -1)
		ft_putchar_err(base[nb], 1, len);
	if (nb >= blen)
	{
		ft_putunbr_b(nb / blen, base, len);
		ft_putunbr_b(nb % blen, base, len);
	}
	return (*len);
}
