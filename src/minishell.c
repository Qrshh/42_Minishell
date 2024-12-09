/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:10:08 by abesneux          #+#    #+#             */
/*   Updated: 2024/11/20 18:24:34 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

void	init_cmd_1(t_cmd *cmd)
{
	cmd->input = NULL;
	cmd->list = NULL;
	cmd->args = NULL;
	cmd->post_pipe = NULL;
	init_signals();
}

t_word	*token(t_cmd *cmd, t_arena *arena)
{
	t_token_list	tokens;
	int				i;

	tokens.head = NULL;
	tokens.current = NULL;
	i = 0;
	while (i < (int)ft_strlen(cmd->input))
	{
		skip_whitespaces(cmd->input, &i);
		if (is_operator(cmd->input[i]))
			handle_operator(cmd->input, &i, &tokens, arena);
		else if (cmd->input[i] == '\'')
			handle_single_quote(cmd->input, &i, &tokens, arena);
		else if (cmd->input[i] == '"')
			handle_double_quote(cmd->input, &i, &tokens, arena);
		else if ((cmd->input[i] == '$' && ft_isalpha(cmd->input[i + 1]))
			|| (cmd->input[i + 1] == '?'))
			handle_env(cmd->input, &i, &tokens, arena);
		else
			handle_word(cmd->input, &i, &tokens, arena);
		i++;
	}
	return (tokens.head);
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

void	shell_loop(t_cmd *cmd, t_env *env, t_arena *arena)
{
	while (1)
	{
		cmd->input = read_and_trim_input(arena);
		init_signals();
		if (!cmd->input)
			break ;
		if (cmd->input[0] == '\0')
			continue ;
		if (!check_syntax(cmd))
		{
			cmd->list = token(cmd, arena);
			cmd->list = handle_dollar(cmd, env, arena);
			merge_quoted_tokens(&(cmd->list), arena);
			pre_execute(cmd, env, cmd->input, arena);
		}
		reset_cmd(cmd);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;
	t_env	env;
	t_arena	arena;

	(void)av;
	arena_init(&arena, ARENA_SIZE);
	env.env_cpy = copy_env(envp, &arena);
	cmd = arena_alloc(&arena, sizeof(t_cmd));
	if (!cmd)
	{
		printf("Error while allocating cmd\n");
		return (1);
	}
	init_cmd_1(cmd);
	if (ac == 1)
		shell_loop(cmd, &env, &arena);
	clear_history();
	free_arena(&arena);
	return (0);
}
