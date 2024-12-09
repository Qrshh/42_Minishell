/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:25:33 by abesneux          #+#    #+#             */
/*   Updated: 2024/11/21 15:05:37 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_list(t_word **head, t_word **current, t_word *new_node)
{
	if (*current == NULL)
	{
		*head = new_node;
		new_node->index = 0;
	}
	else
	{
		new_node->index = (*current)->index + 1;
		(*current)->next = new_node;
		new_node->previous = *current;
	}
	*current = new_node;
}

void	handle_operator(char *input, int *i, t_token_list *tokens,
			t_arena *arena)
{
	t_token	token;
	char	*temp;
	int		len;
	t_word	*new_node;
	int		flag[2];

	len = 1;
	ft_memset(flag, 0, sizeof(int) * 2);
	token = PIPE;
	if ((input[*i] == '>' || input[*i] == '<') && input[*i + 1] == input[*i])
	{
		len = 2;
		if (input[*i] == '<')
			token = DOUBLE_LEFT;
		else
			token = DOUBLE_RIGHT;
	}
	else if (input[*i] == '<')
		token = LEFT;
	else if (input[*i] == '>')
		token = RIGHT;
	temp = aft_strndup(&input[*i], len, arena);
	new_node = init_lex(temp, token, flag, arena);
	add_to_list(&tokens->head, &tokens->current, new_node);
	*i += len - 1;
}

void	handle_single_quote(char *input, int *i, t_token_list *tokens,
			t_arena *arena)
{
	char	*word;
	int		j;
	t_word	*new_node;
	int		flag[2];

	flag[0] = 0;
	flag[1] = 0;
	j = *i + 1;
	flag[0] = check_space_before(input, i);
	while (input[j] && input[j] != '\'')
		j++;
	if (input[j] == '\'')
	{
		flag[1] = check_space_after(input, j);
		word = aft_strndup(&input[*i + 1], j - *i - 1, arena);
		new_node = init_lex(word, SINGLE_QUOTE, flag, arena);
		add_to_list(&tokens->head, &tokens->current, new_node);
		*i = j;
	}
}

void	handle_word(char *input, int *i, t_token_list *tokens,
			t_arena *arena)
{
	int		len;
	char	*word;
	t_word	*new_node;
	int		flag[2];

	flag[0] = 0;
	flag[1] = 0;
	len = 0;
	flag[0] = check_space_before(input, i);
	while (input[*i + len] && !is_space(input[*i + len])
		&& !is_operator(input[*i + len]))
	{
		if (input[*i + len] == '"' || input[*i + len] == '\'')
			break ;
		len++;
	}
	flag[1] = check_space_after(input, *i + len - 1);
	word = aft_strndup(&input[*i], len, arena);
	new_node = init_lex(word, WORD, flag, arena);
	add_to_list(&tokens->head, &tokens->current, new_node);
	*i += len - 1;
}

void	handle_env(char *input, int *i, t_token_list *tokens, t_arena *arena)
{
	char	*word;
	int		j;
	t_word	*new_node;
	int		flag[2];

	while (input[*i] && input[*i] == '$')
	{
		flag[0] = check_space_before(input, i);
		j = *i + 1;
		while (input[j] && !is_space(input[j]) && input[j] != '"'
			&& input[j] != '\'' && input[j] != ';' && input[j] != '$')
			j++;
		if (j > *i + 1)
		{
			flag[1] = check_space_after(input, j - 1);
			word = aft_strndup(&input[*i + 1], j - *i - 1, arena);
			new_node = init_lex(word, V_ENV, flag, arena);
			add_to_list(&tokens->head, &tokens->current, new_node);
			*i = j - 1;
		}
		*i += 1;
	}
}
