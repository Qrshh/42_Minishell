/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:46:09 by abesneux          #+#    #+#             */
/*   Updated: 2024/11/08 13:02:23 by ozdemir          ###   ########.fr       */
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
    int flag1;
    int flag2;

    flag1= 0;
    flag2 = 0;
	j = *i + 1;
    flag1 = check_space_before(input, i);
	while (input[j] && input[j] != '"' )
    {
        if(input[j] == '$')
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
