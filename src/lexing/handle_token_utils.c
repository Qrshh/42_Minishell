/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:46:09 by abesneux          #+#    #+#             */
/*   Updated: 2024/11/20 18:24:26 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*merge_content(t_word *current, t_arena *arena)
{
	char	*merged_content;
	t_word	*next;

	merged_content = aft_strdup(current->str, arena);
	while (current->next && (current->next->token == SINGLE_QUOTE
			|| current->next->token == DOUBLE_QUOTE
			|| current->next->token == WORD || current->next->token == V_ENV)
		&& !current->has_space_after && !current->next->has_space_before)
	{
		next = current->next;
		merged_content = aft_strjoin(merged_content, next->str, arena);
		current->next = next->next;
		if (next->next)
			next->next->previous = current;
	}
	return (merged_content);
}

void	merge_quoted_tokens(t_word **head, t_arena *arena)
{
	t_word	*current;

	current = *head;
	while (current)
	{
		if (current->token == WORD || current->token == SINGLE_QUOTE
			|| current->token == DOUBLE_QUOTE || current->token == V_ENV)
		{
			current->str = merge_content(current, arena);
			current->token = WORD;
		}
		current = current->next;
	}
}

void	handle_double_quote(char *input, int *i, t_token_list *tokens,
			t_arena *arena)
{
	char	*word;
	int		j;
	t_word	*new_node;
	int		flag[2];

	flag[0] = 0;
	flag[1] = 0;
	j = *i + 1;
	flag[0] = check_space_before(input, i);
	while (input[j] && input[j] != '"')
	{
		if (input[j] == '$')
			return ;
		j++;
	}
	if (input[j] == '"')
	{
		flag[1] = check_space_after(input, j);
		word = aft_strndup(&input[*i + 1], j - *i - 1, arena);
		new_node = init_lex(word, DOUBLE_QUOTE, flag, arena);
		add_to_list(&tokens->head, &tokens->current, new_node);
		*i = j;
	}
}

int	is_token_redir(t_word *list)
{
	if (list->token == LEFT || list->token == RIGHT
		|| list->token == DOUBLE_LEFT || list->token == DOUBLE_RIGHT)
		return (1);
	return (0);
}
