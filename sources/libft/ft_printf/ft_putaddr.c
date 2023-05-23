/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:23:25 by jprofit           #+#    #+#             */
/*   Updated: 2022/12/12 13:58:05 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

ssize_t	ft_putaddr(unsigned long l, char *str, ssize_t *len)
{
	if (ft_putstr_err("0x", 1, len) == -1)
		return (-1);
	if (ft_putunbr_b(l, str, len) == -1)
		return (-1);
	return (*len);
}
