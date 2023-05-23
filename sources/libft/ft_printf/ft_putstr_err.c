/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 09:32:33 by jprofit           #+#    #+#             */
/*   Updated: 2022/12/12 13:58:11 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

ssize_t	ft_putstr_err(char *s, int fd, ssize_t *len)
{
	if (s == NULL)
	{
		ft_putstr_err("(null)", fd, len);
		return (*len);
	}
	while (*s && *len != -1)
	{
		ft_putchar_err(*s, fd, len);
		s++;
	}
	return (*len);
}
