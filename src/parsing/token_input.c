/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:13:13 by abesneux          #+#    #+#             */
/*   Updated: 2024/08/07 21:17:57 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_list(t_word **list)
{
	*list = (t_word *)malloc(sizeof(t_word));
	if(*list)
	{
		(*list)->str = NULL;
		(*list)->quote = 0;
		(*list)->has_space = 0;
		(*list)->next = NULL;
		(*list)->previous = NULL;
	}
}

void	add_token_to_list(t_word **list, char *input, char quote, int has_space)
{
	if(!*list)
	{
		initialize_list(list);
		if(!*list)
			return ;
	}
	else 
	{
		t_word *new_node = (t_word *)malloc(sizeof(t_word));
		if(!new_node)
			return ;
		new_node->str = ft_strdup(input);
		if(!new_node->str)
		{
			free(new_node);
			return ;
		}
		new_node->quote = quote;
		new_node->has_space = has_space;
		new_node->next = NULL;

		t_word *current = *list;
		while(current->next)
			current = current->next;
		current->next = new_node;
		new_node->previous = current;
	}
}

char	*get_word(char *input, int *i)
{
	char *word;
	char quote;
	int j;

	//je malloc de la taille de l'input au cas ou il y a que 1 seul mot et comme ca ya pas de depassement et c pas fixe
	word = (char *)malloc(ft_strlen(input) * sizeof(char));
	if(!word)
		return NULL;
	j = 0;
	if(input[*i] == '"' || input[*i] == '\'')
	{
		quote = input[*i];
		(*i)++;
	}
	else 
		quote = 0;
	while(input[*i])
	{
		if(quote == 0 && (ft_isspace(input[*i]) || input[*i] == '>'))
			break;
		else if (input[*i] == quote)
		{
			(*i)++;
			break;
		}
		word[j] = input[*i];
		j++;
		(*i)++;
	}
	word[j] = '\0';
	return(word);
}

/*
Vérification des guillemets : Si le caractère actuel est un guillemet simple ou double, on le stocke et on avance l'indice.
Extraction du mot : On copie les caractères de la chaîne d'entrée jusqu'à rencontrer un espace, un caractère spécial (ici '>'), ou le guillemet de fin.
Terminaison du mot : On ajoute le caractère nul ('\0') à la fin du mot pour le terminer correctement en tant que chaîne de caractères en C.
Retour du mot : La fonction retourne le mot extrait.
*/

t_word *tokenize(char *input)
{
	int i;
	char *add;
	t_word *list;

	list = NULL;
	i = 0;
	while(input[i])
	{
		while(ft_isspace(input[i]))
			i++;
		add = get_word(input, &i);
		if(add)
		{
			add_token_to_list(&list, add, 0, 0);
			free(add);
		}
		i++;
	}
	return list;
}
