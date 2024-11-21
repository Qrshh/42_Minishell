/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:43:09 by abesneux          #+#    #+#             */
/*   Updated: 2024/11/12 20:31:13 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_word	*init_lex(char *str, t_token token, int flag1, int flag2)
{
	t_word	*node;
	int		i;

	i = 0;
	node = malloc(sizeof(t_word));
	if (!node)
		return (NULL);
	node->str = ft_strdup(str);
	node->token = token;
	node->index = i++;
	if (flag1)
		node->has_space_before = true;
	else
		node->has_space_before = false;
	if (flag2)
		node->has_space_after = true;
	else
		node->has_space_after = false;
	node->previous = NULL;
	node->next = NULL;
	return (node);
}

int	check_space_before(char *input, int *i)
{
	if (*i > 0 && is_space(input[*(i)-1]))
		return (1);
	return (0);
}

int	check_space_after(char *input, int i)
{
	if (input[i] && input[i + 1] && is_space(input[i + 1]))
		return (1);
	return (0);
}
