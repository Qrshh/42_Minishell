/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrshh <qrshh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:10:08 by abesneux          #+#    #+#             */
/*   Updated: 2024/05/31 07:16:01 by qrshh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_sh(t_all *all)
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
		return(reset_all(all));
	add_history(all->input);
	// execute_command(all->input, env); en commentaire car pas comme ca qu'on imagine la vie
	reset_all(all);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_all	*all;

	(void)av;
	(void)env;
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
	init_sh(all);
	free(all);
	return (0);
}
