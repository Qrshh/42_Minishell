/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:23:20 by abesneux          #+#    #+#             */
/*   Updated: 2024/09/04 15:18:00 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	word_len(char *input, int i)
{
	int	j;

	j = i;
	while (input[j] && !is_space(input[i]) && !is_operator(input[j]
			&& !is_quote(input[j])))
		j++;
	return (j - i);
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
