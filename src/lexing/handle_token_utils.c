/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:46:09 by abesneux          #+#    #+#             */
/*   Updated: 2024/10/01 20:36:36 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_double_quote(char *input, int *i, t_word **head,
		t_word **current)
{
	char	*word;
	int		j;
	t_word	*new_node;

	j = *i + 1;
	while (input[j] && input[j] != '\'')
		j++;
	if (input[j] == '"')
	{
		word = ft_strndup(&input[*i + 1], j - *i - 1);
		new_node = init_lex(word, WORD);
		add_to_list(head, current, new_node);
		*i = j;
		free(word);
	}
}
