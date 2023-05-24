/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:30:18 by jprofit           #+#    #+#             */
/*   Updated: 2023/05/22 12:30:18 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
 * for performances purpose the length will stay squared
 * because square root take a lot of perf and because we can avoid them
 */
int get_seg_length_squared(t_vector vec1, t_vector vec2)
{
	return ((vec2.x - vec1.x) * (vec2.x - vec1.x) + (vec2.y - vec1.y) * (vec2.y - vec1.y));
}
