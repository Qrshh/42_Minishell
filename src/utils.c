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

char **split_input(char *input)
{
    char **splited_input = ft_split(input, ';');
    if (!splited_input)
    {
        splited_input = malloc(2 * sizeof(char *));
        splited_input[0] = ft_strdup(input);
        splited_input[1] = NULL;
    }
    return splited_input;
}

void process_command(char *command, t_token *tokens, t_all *all)
{
    char *trimmed_command = ft_strtrim(command, " \t");
    if (trimmed_command && *trimmed_command)
    {
        free(command);
        command = trimmed_command;
        all->input = command;
        tokenize(all, &tokens);
    }
    else
        free(trimmed_command);
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

int	reset_all(t_all *all)
{
	if (all->input)
	{
		free(all->input);
		all->input = NULL;
	}
	if (all->splited_input)
	{
		free_tab(all->splited_input);
		all->splited_input = NULL;
	}
	return 1;
}
