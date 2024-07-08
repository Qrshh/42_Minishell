/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrshh <qrshh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:10:08 by abesneux          #+#    #+#             */
/*   Updated: 2024/07/05 19:58:57 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_loop(t_all *all, t_token *tokens)
{
	while (1)
	{
		all->input = readline("> ");
		if (!all->input)
			break ;
		add_history(all->input);
		all->input = ft_strtrim(all->input, " \t");
		if (!check_syntax(all->input))
			tokenize(all, &tokens);
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
		printf("Error while malloc\n");
		return (1);
	}
	if (ac == 1)
		shell_loop(all, tokens);
	free(all);
	clear_history();
	return (0);
}
