/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:10:08 by abesneux          #+#    #+#             */
/*   Updated: 2024/05/29 16:30:32 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_sh(t_all *all, char **env)
{
	char	*temp;

	all->input = readline("MINISHELL $ ");
	if (!all->input)
	{
		printf("exit\n");
		exit(0);
	}
	temp = ft_strtrim(all->input, " ");
	free(all->input);
	all->input = temp;
	if (all->input[0] == '\0')
	{
		reset_all(all);
		return (0);
	}
	add_history(all->input);
	execute_command(all->input, env);
	reset_all(all);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_all	*all;

	(void)av;
	if (ac != 1)
	{
		printf("Error: Too many arguments\n");
		return (1);
	}
	all = malloc(sizeof(t_all));
	if (!all)
	{
		printf("Error while malloc\n");
		return (1);
	}
	while (1)
	{
		if (!init_sh(all, env))
			continue ;
	}
	free(all);
	return (0);
}
