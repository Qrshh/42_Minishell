/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrshh <qrshh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:07:54 by qrshh             #+#    #+#             */
/*   Updated: 2024/05/23 21:12:04 by qrshh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_all(t_all *all)
{
	all->input = NULL;
	all->splited_input = NULL;
}

int	reset_all(t_all *all)
{
	free(all->input);
	all->input = NULL;
	return (1);
}
