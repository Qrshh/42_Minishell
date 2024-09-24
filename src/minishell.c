/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:10:08 by abesneux          #+#    #+#             */
/*   Updated: 2024/09/23 16:12:24 by ozdemir          ###   ########.fr       */
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

char	*dollar_question(char *line)
{
	int		len;
	int		new_len;
	char	*result;

	len = strlen(line);
	new_len = len;
	int i, j, num_digits;
	// Compter le nombre de "$?" dans la ligne
	for (i = 0; i < len - 1; i++)
	{
		if (line[i] == '$' && line[i + 1] == '?')
		{
			num_digits = get_num_digits(g_exit_status);
			new_len += num_digits - 2;
		}
	}
	// Allouer de la mémoire pour le nouveau string
	result = malloc(new_len + 1);
	// Remplacer les "$?" par la valeur de g_exit_status
	for (i = 0, j = 0; i < len; i++)
	{
		if (line[i] == '$' && line[i + 1] == '?')
		{
			sprintf(result + j, "%d", g_exit_status);
			j += get_num_digits(g_exit_status);
			i++;
		}
		else
		{
			result[j++] = line[i];
		}
	}
	result[j] = '\0';
	return (result);
}

void	shell_loop(t_all *all, t_env *env)
{
	char	*sig;

	while (1)
	{
		all->input = read_and_trim_input();
		if (!all->input)
			break ;
		if (all->input[0] == '\0')
		{
			free(all->input);
			continue;
		}
		if (!check_syntax(all->input))
		{
			all->list = token(all);
			sig = dollar_question(all->input);
			print_list(all);
			pre_execute(all->list, env);
			free(sig);
		}
		reset_all(all);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_all	*all;
	t_env env;

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
