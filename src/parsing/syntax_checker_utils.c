/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 00:53:58 by qrshh             #+#    #+#             */
/*   Updated: 2024/07/08 20:14:14 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
