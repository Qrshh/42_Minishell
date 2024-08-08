/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:10:08 by abesneux          #+#    #+#             */
/*   Updated: 2024/08/08 21:47:04 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_all(t_all *all)
{
	all->input = NULL;
	all->list = NULL;
	all->splited_input = NULL;
	init_signals();
}

void shell_loop(t_all *all)
{
	int i;

    while (1)
    {
		i = 0;
        all->input = read_and_trim_input();
        if (!all->input)
            break;
        if (!check_syntax(all->input))
		{
			all->splited_input = split_on_semicolon(all->input);
			while(all->splited_input[i])
			{
				ft_printf("%d\n", i);
				all->list = tokenize(all->splited_input[i++]);
				print_list(all->list);
				//send la liste apres comme ca je peux la free tranquille pour la suivante
			}
		}
        reset_all(all);
    }
}

int	main(int ac, char **av, char **env)
{
	t_all		*all;

	(void)av;
	(void)env;
	all = malloc(sizeof(t_all));
	init_all(all);
	if (!all)
	{
		ft_printf("Error while malloc\n");
		return (1);
	}
	if (ac == 1)
		shell_loop(all);
	free(all);
	clear_history();
	return (0);
}
