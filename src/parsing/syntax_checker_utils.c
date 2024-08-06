/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 00:53:58 by qrshh             #+#    #+#             */
/*   Updated: 2024/07/22 16:32:58 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_quotes_count(char c, int *s_quotes, int *d_quotes)
{
	if (c == 34)
		(*d_quotes)++;
	else if (c == 39)
		(*s_quotes)++;
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int check_semicolon(char *input)
{
	if(ft_strcmp(input, ";"))
		return(1);
	return(0);
}
