/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:10:08 by abesneux          #+#    #+#             */
/*   Updated: 2024/06/10 14:49:06 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    shell_loop(t_all *all)
{
    while(1)
    {
        all->input = readline("> ");
        if(!all->input)
            break;
        add_history(all->input);
        if(check_syntax(all->input))
            //TODO: Appeler la fonction pour tokeniser
            reset_all(all);
        reset_all(all);
    }
}

int	main(int ac, char **av, char **env)
{
	t_all	*all;

	(void)av;
	(void)env;
	all = malloc(sizeof(t_all));
	if (!all)
	{
		printf("Error while malloc\n");
		return (1);
	}
    if(ac == 1)
	    shell_loop(all);
	free(all);
	return (0);
}
