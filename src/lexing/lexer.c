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

t_word	*init_lex(char *str, t_token token, int flag[2], t_arena *arena)
{
	t_word	*node;
	int		i;

	i = 0;
	node = arena_alloc(arena, sizeof(t_word));
	if (!node)
		return (NULL);
	node->str = aft_strdup(str, arena);
	node->token = token;
	node->index = i++;
	if (flag[0])
		node->has_space_before = true;
	else
		node->has_space_before = false;
	if (flag[1])
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
