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

char	*read_and_trim_input(void)
{
	char	*input;
	char	*trimmed_input;

	input = readline("> ");
	if (!input)
		return (NULL);
	else if (*input)
		add_history(input);
	trimmed_input = ft_strtrim(input, " \t");
	free(input);
	return (trimmed_input);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	skip_whitespaces(char *input, int *i)
{
	while (is_space(input[*i]))
		(*i)++;
}

int	reset_all(t_all *all)
{
	t_word	*current;
	t_word	*next;

	if (all->input)
	{
		free(all->input);
		all->input = NULL;
	}
	current = all->list;
	while (current)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
	all->list = NULL;
	return (1);
}

void	print_list(t_all *all)
{
	t_word	*current;

	current = all->list;
	while (current != NULL)
	{
		printf("Index: %d\n", current->index);
		printf("String: %s\n", current->str);
		printf("Token: %d\n", current->token);
		printf("----------\n");
		current = current->next;
	}
}
