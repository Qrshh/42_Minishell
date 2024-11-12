/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:46:09 by abesneux          #+#    #+#             */
/*   Updated: 2024/11/12 20:31:00 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	merge_quoted_tokens(t_word **head)
{
	t_word	*current;
	t_word	*next;
	char	*merged_content;
	char	*temp;

	current = *head;
	while (current)
	{
		if (current->token == WORD || current->token == SINGLE_QUOTE
			|| current->token == DOUBLE_QUOTE)
		{
			merged_content = ft_strdup(current->str);
			while (current->next && (current->next->token == SINGLE_QUOTE
					|| current->next->token == DOUBLE_QUOTE
					|| current->next->token == WORD)
				&& !current->has_space_after
				&& !current->next->has_space_before)
			{
				next = current->next;
				temp = merged_content;
				merged_content = ft_strjoin(merged_content, next->str);
				free(temp);
				current->next = next->next;
				if (next->next)
					next->next->previous = current;
				free(next->str);
				free(next);
			}
			free(current->str);
			current->str = merged_content;
			current->token = WORD;
		}
		current = current->next;
	}
}

void	handle_double_quote(char *input, int *i, t_word **head,
		t_word **current)
{
	char	*word;
	int		j;
	t_word	*new_node;
	int		flag1;
	int		flag2;

	flag1 = 0;
	flag2 = 0;
	j = *i + 1;
	flag1 = check_space_before(input, i);
	while (input[j] && input[j] != '"')
	{
		if (input[j] == '$')
			return ;
		j++;
	}
	if (input[j] == '"')
	{
		flag2 = check_space_after(input, j);
		word = ft_strndup(&input[*i + 1], j - *i - 1);
		new_node = init_lex(word, DOUBLE_QUOTE, flag1, flag2);
		add_to_list(head, current, new_node);
		*i = j;
		free(word);
	}
}

int	is_token_redir(t_word *list)
{
	if (list->token == LEFT || list->token == RIGHT
		|| list->token == DOUBLE_LEFT || list->token == DOUBLE_RIGHT)
		return (1);
	return (0);
}
