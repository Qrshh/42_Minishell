/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:10:08 by abesneux          #+#    #+#             */
/*   Updated: 2024/08/09 21:55:41 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_all(t_all *all)
{
	all->input = NULL;
	all->list = NULL;
	init_signals();
}

t_word	*token(t_all *all)
{
	t_word 	*head;
	t_word	*current;
	int		len;
	int		i;
	
	head = NULL;
	current = NULL;
	len = ft_strlen(all->input);
	i = 0;
	while(i < len)
	{
		skip_whitespaces(all->input, &i);
		if(is_operator(all->input[i]))
			handle_operator(all->input, &i, &current, all->input[i]);
		else if (all->input[i] == '\'')
			handle_single_quote(all->input, &i, &current, all->input[i]);
		else
			hanlde_word(all->input, &i, &current, all);
	}
}

void shell_loop(t_all *all)
{
    while (1)
    {
        all->input = read_and_trim_input();
        if (!all->input)
            break;
        if (!check_syntax(all->input))
		{
			all->list = token(all);
			print_list(all->list);
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
