/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:46:09 by abesneux          #+#    #+#             */
/*   Updated: 2024/11/07 17:06:24 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void merge_quoted_tokens(t_word **head)
{
    t_word *current = *head;
    t_word *next;
    char *merged_content;

    while (current)
    {
        // Si le token est de type WORD ou guillemets
        if (current->token == WORD || current->token == SINGLE_QUOTE || current->token == DOUBLE_QUOTE)
        {
            // Initialiser le contenu fusionné avec le contenu du token actuel
            merged_content = ft_strdup(current->str);

            // Fusionner avec les tokens suivants tant qu'ils sont adjacents, de type guillemets ou WORD, et sans espace entre eux
            while (current->next &&
                   (current->next->token == SINGLE_QUOTE || current->next->token == DOUBLE_QUOTE || current->next->token == WORD) &&
                   !current->has_space_after && !current->next->has_space_before)
            {
                next = current->next;
                
                // Ajouter le contenu du token suivant
                char *temp = merged_content;
                merged_content = ft_strjoin(merged_content, next->str);
                free(temp);

                // Mettre à jour la liste chaînée pour supprimer le token suivant
                current->next = next->next;
                if (next->next)
                    next->next->previous = current;

                // Libérer la mémoire du token fusionné
                free(next->str);
                free(next);
            }

            // Mettre à jour le token courant avec le contenu fusionné
            free(current->str);
            current->str = merged_content;
            current->token = WORD;  // Le token fusionné devient un mot normal
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
