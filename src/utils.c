/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrshh <qrshh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:07:54 by qrshh             #+#    #+#             */
/*   Updated: 2024/05/23 21:12:04 by qrshh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *read_and_trim_input(void)
{
    char *input = readline("> ");
    if (!input)
        return NULL;
    add_history(input);
    char *trimmed_input = ft_strtrim(input, " \t");
    free(input);
    return trimmed_input;
}

void	free_tab(char **tab)
{
	int 	i;
	
	i = 0;
	while(tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void    skip_whitespaces(char *input, int *i)
{
    while(is_space(input[*i]))
        (*i)++;
}

int	reset_all(t_all *all)
{
	if (all->input)
	{
		free(all->input);
		all->input = NULL;
	}
    t_word *current = all->list;
    t_word *next;
    while (current) {
        next = current->next;
        free(current->str);
        free(current);
        current = next;
    }
    all->list = NULL;
	return 1;
}
void print_list(t_all *all)
{
    t_word *current = all->list; // Commencez par le premier élément de la liste

    while (current != NULL)
    {
        // Affichez les informations que vous souhaitez pour chaque élément
        printf("Index: %d\n", current->index);
        printf("String: %s\n", current->str);
        printf("Token: %d\n", current->token); // Supposez que t_token est un type numérique, sinon adaptez
        printf("----------\n");

        // Passez à l'élément suivant dans la liste chaînée
        current = current->next;
    }
}


