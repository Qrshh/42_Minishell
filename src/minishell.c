/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:10:08 by abesneux          #+#    #+#             */
/*   Updated: 2024/10/30 20:19:30 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status = 0;

void	init_all(t_all *all)
{
	all->input = NULL;
	all->list = NULL;
	init_signals();
}

t_word	*token(t_all *all)
{
	t_word	*head;
	t_word	*current;
	int		len;
	int		i;

	head = NULL;
	current = NULL;
	len = ft_strlen(all->input);
	i = 0;
	while (i < len)
	{
		skip_whitespaces(all->input, &i);
		if (is_operator(all->input[i]))
			handle_operator(all->input, &i, &head, &current);
		else if (all->input[i] == '\'')
			handle_single_quote(all->input, &i, &head, &current);
		else if (all->input[i] == '"')
			handle_double_quote(all->input, &i, &head, &current);
		else if ((all->input[i] == '$' && ft_isalpha(all->input[i + 1])) || (all->input[i + 1] == '?'))
			handle_env(all->input, &i, &head, &current);
		else
			handle_word(all->input, &i, &head, &current);
		i++;
	}
	return (head);
}

int	get_num_digits(int num)
{
	int	count;

	count = 0;
	while (num != 0)
	{
		count++;
		num /= 10;
	}
	return (count);
}

void	shell_loop(t_all *all, t_env *env)
{
	while (1)
	{
		all->input = read_and_trim_input();
		if (!all->input)
			break ;
		if (all->input[0] == '\0')
		{
			free(all->input);
			continue ;
		}
		if (!check_syntax(all->input))
		{
			all->list = token(all);
			print_list(all);
			all->list = handle_dollar(all, env);
			merge_quoted_tokens(&(all->list), SINGLE_QUOTE);
			merge_quoted_tokens(&(all->list), DOUBLE_QUOTE);
			pre_execute(all->list, env);
		}
		reset_all(all);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_all	*all;
	t_env	env;

	(void)av;
	env.env_cpy = copy_env(envp);
	all = malloc(sizeof(t_all));
	init_all(all);
	if (!all)
	{
		printf("Error while malloc\n");
		return (1);
	}
	if (ac == 1)
		shell_loop(all, &env);
	free(all);
	clear_history();
	return (0);
}
