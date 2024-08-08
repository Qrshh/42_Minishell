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

int     ft_isspace(char c)
{
    if((c >= 9 && c <= 13) || c == 32)
        return (1);
    return(0);
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

void print_list(t_word *list)
{
    t_word *current = list;

    while (current)
    {
        printf("Word: %s, Quote: %c, Has Space: %d\n", 
                current->str, 
                current->quote, 
                current->has_space);
        current = current->next;
    }
}

char **split_on_semicolon(char *input)
{
    char **result;
    int count;
    char quote;
    char *start;
    char *temp;

    start = input;
    quote = 0;
    count = 0;
    result = NULL;

    while(*input)
    {
        if(*input == '"' || *input == '\'')
        {
            if(quote == 0)
                quote = *input;
            else if (quote == *input)
                quote = 0;
        }
        else if (*input == ';' && quote == 0)
        {
            result = realloc(result, (count + 2) * sizeof(char *));
            temp = ft_strndup(start, input - start);
            result[count++] = temp;
            start = input + 1;
        }
        input++;
    }
    result = realloc(result, (count + 2) * sizeof(char *));
    result[count++] = strdup(start);
    result[count] = NULL;  // Terminer la liste par NULL

    return result;
}

