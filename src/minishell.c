/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrshh <qrshh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:10:08 by abesneux          #+#    #+#             */
/*   Updated: 2024/06/17 14:59:51 by qrshh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_loop(t_all *all)
{
	char *trimmed_input;

	while (1)
	{
		all->input = readline("> ");
		if (!all->input)
			break ;
		add_history(all->input);
		trimmed_input = ft_strtrim(all->input, " \t");
		if (!check_syntax(trimmed_input))
		{
			cut_input(trimmed_input);
		}
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
	if (ac == 1)
		shell_loop(all);
	free(all);
    clear_history();
	return (0);
}
