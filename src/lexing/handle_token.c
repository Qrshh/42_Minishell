/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:25:33 by abesneux          #+#    #+#             */
/*   Updated: 2024/08/22 18:22:10 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_to_list(t_word **head, t_word **current, t_word *new_node)
{
	if (*current == NULL)
	{
		*head = new_node;            // Premier élément de la liste
		new_node->index = 0;         // Premier élément, index 0
	}
	else
	{
		new_node->index = (*current)->index + 1;  // Incrément de l'index
		(*current)->next = new_node;              // Lier le précédent au nouveau
		new_node->previous = *current;            // Lier le nouveau au précédent
	}
	*current = new_node;  // Déplacer le pointeur `current` sur le nouvel élément
}

void handle_operator(char *input, int *i, t_word **head, t_word **current, char operator)
{
	t_token token;
	char *temp;
	int len;

	len = 1;
	if (operator == '|')
		token = PIPE;
	else if ((operator == '>' || operator == '<') && input[*i + 1] == operator)
	{
		len = 2;
		token = (operator == '<') ? DOUBLE_LEFT : DOUBLE_RIGHT;
	}
	else
		token = (operator == '<') ? LEFT : RIGHT;

	temp = ft_strndup(&input[*i], len);
	t_word *new_node = init_lex(temp, token);
	add_to_list(head, current, new_node);
	*i += len - 1; // Avancez de 2 si double opérateur, sinon 1
	free(temp);
}

void handle_single_quote(char *input, int *i, t_word **head, t_word **current, char quote)
{
	char *word;
	int j = *i + 1;

	while (input[j] && input[j] != quote)
		j++;

	if (input[j] == quote)
	{
		word = ft_strndup(&input[*i + 1], j - *i - 1); // Capture le contenu entre guillemets
		t_word *new_node = init_lex(word, WORD);
		add_to_list(head, current, new_node);
		*i = j;  // Positionner l'index à la fin du guillemet fermant
		free(word);
	}
}

void handle_word(char *input, int *i, t_word **head, t_word **current, t_all *all)
{
	int len = 0;
	char *word;
	(void)all;

	// Compte les caractères jusqu'à un espace ou un token spécial
	while (input[*i + len] && !is_space(input[*i + len]) && !is_operator(input[*i + len]))
	{
		if (input[*i + len] == '"' || input[*i + len] == '\'')
			break;
		len++;
	}

	word = ft_strndup(&input[*i], len);
	t_word *new_node = init_lex(word, WORD);
	add_to_list(head, current, new_node);
	*i += len - 1;  // Déplacez l'index à la fin du mot traité
	free(word);
}

