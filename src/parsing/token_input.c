/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:13:13 by abesneux          #+#    #+#             */
/*   Updated: 2024/08/08 21:52:33 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//initalize la liste qui permet de stocker les mots
void	initialize_list(t_word **list, char *input, char quote, int has_space)
{
	*list = (t_word *)malloc(sizeof(t_word));
	if (*list)
	{
		(*list)->str = ft_strdup(input);
		if (!(*list)->str) 
		{
			free(*list);
			*list = NULL;
			return ;
		}
		(*list)->quote = quote;
		(*list)->has_space = has_space;
		(*list)->next = NULL;
		(*list)->previous = NULL;
	}
}
//permet de creer la liste etc etc (on va pouvoir l'utiliser apres let's go)
void	add_token_to_list(t_word **list, char *input, char quote, int has_space)
{
	t_word *new_node;

	new_node = (t_word *)malloc(sizeof(t_word));
	if (!new_node)
		return ;
	new_node->str = ft_strdup(input);
	if (!new_node->str)
	{
		free(new_node);
		return ;
	}
	new_node->quote = quote;
	new_node->has_space = has_space;
	new_node->next = NULL;
	if (!*list)
	{
		new_node->previous = NULL;
		*list = new_node;
	}
	else
	{
		t_word *current = *list;
		while (current->next)
			current = current->next;
		current->next = new_node;
		new_node->previous = current;
	}
}
//permet d'obtenir le "mot" ou suite de mot si il y a des quotes
char	*get_word(char *input, int *i, char *quote, int *has_space)
{
	char *word;
	int j;

	word = (char *)malloc((ft_strlen(input) + 1) * sizeof(char));
	if (!word)
		return NULL;

	j = 0;
	*quote = 0;  // Initialise la valeur de quote
	//IL FAUT RENDRE LA QUOTE INVALIDE SI IL Y A UN \ DEVANT GENRE
	if ((input[*i] == '"' || input[*i] == '\''))
	{
		*quote = input[*i];
		(*i)++;
	}
	else 
		*quote = 0;
	while (input[*i])
	{
		if (*quote == 0 && (ft_isspace(input[*i]) || input[*i] == '>'))
			break;
		else if (input[*i] == *quote)
		{
			(*i)++;
			break;
		}
		word[j++] = input[*i];
		(*i)++;
	}
	word[j] = '\0';

	*has_space = 0;
	if (ft_isspace(input[*i]))
		*has_space = 1;

	return word;
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
	char quote;
	int has_space;

	list = NULL;
	i = 0;

	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;

		add = get_word(input, &i, &quote, &has_space);

		if (add)
		{
			add_token_to_list(&list, add, quote, has_space);
			free(add);
		}
		i++;
	}

	return list;
}


