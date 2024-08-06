/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:10:08 by abesneux          #+#    #+#             */
/*   Updated: 2024/08/05 21:02:51 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_all(t_all *all)
{
	all->input = NULL;
	all->splited_input = NULL;
	init_signals();
}

void shell_loop(t_all *all, t_token *tokens)
{
	int		i;
    while (1)
    {
        all->input = read_and_trim_input();
        if (!all->input)
            break;
        all->splited_input = split_input(all->input);
        if (!check_syntax(all->splited_input))
        {
            i = 0;
            while (all->splited_input[i])
            {
                process_command(all->splited_input[i], tokens, all);
                i++;
            }
        }
        reset_all(all);
    }
}


int	main(int ac, char **av, char **env)
{
	t_token		*tokens;
	t_all		*all;

	tokens = NULL;
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
		shell_loop(all, tokens);
	free(all);
	clear_history();
	return (0);
}
