/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:46:09 by abesneux          #+#    #+#             */
/*   Updated: 2024/10/28 17:54:11 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void merge_quoted_tokens(t_word **head, t_token quote_type)
{
    t_word *current = *head;
    t_word *next;
    char *merged_content;

    while (current)
    {
        if (current->token == quote_type)
        {
            merged_content = ft_strdup(current->str);
            while (current->next && current->next->token == quote_type)
            {
                next = current->next;
                merged_content = ft_strjoin(merged_content, next->str);
                current->next = next->next;
                if (next->next)
                    next->next->previous = current;

                free(next->str);
                free(next);
            }
            free(current->str);
            ft_printf("test\n");
			current->token = WORD;
            current->str = merged_content;
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

	j = *i + 1;
	while ((input[j] && input[j] != '"') )//|| (input[j] && input[j] != '\''))
		j++;
	if (input[j] == '"')
	{
		word = ft_strndup(&input[*i + 1], j - *i - 1);
		new_node = init_lex(word, DOUBLE_QUOTE);
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
