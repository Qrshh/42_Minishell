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

void	handle_operator(char *input, int *i, t_word **head, t_word **current)
{
	t_token	token;
	char	*temp;
	int		len;
	t_word	*new_node;

	len = 1;
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
	temp = ft_strndup(&input[*i], len);
	new_node = init_lex(temp, token, 0, 0);
	add_to_list(head, current, new_node);
	*i += len - 1;
	free(temp);
}

void	handle_single_quote(char *input, int *i, t_word **head,
		t_word **current)
{
	char	*word;
	int		j;
	t_word	*new_node;
	int		flag1;
	int		flag2;

	flag1 = 0;
	flag2 = 0;
	j = *i + 1;
	flag1 = check_space_before(input, i);
	while (input[j] && input[j] != '\'')
		j++;
	if (input[j] == '\'')
	{
		flag2 = check_space_after(input, j);
		word = ft_strndup(&input[*i + 1], j - *i - 1);
		new_node = init_lex(word, SINGLE_QUOTE, flag1, flag2);
		add_to_list(head, current, new_node);
		*i = j;
		free(word);
	}
}

void	handle_word(char *input, int *i, t_word **head, t_word **current)
{
	int		len;
	char	*word;
	t_word	*new_node;
	int		flag1;
	int		flag2;

	flag1 = 0;
	flag2 = 0;
	len = 0;
	flag1 = check_space_before(input, i);
	while (input[*i + len] && !is_space(input[*i + len])
		&& !is_operator(input[*i + len]))
	{
		if (input[*i + len] == '"' || input[*i + len] == '\'')
			break ;
		len++;
	}
	flag2 = check_space_after(input, *i + len - 1);
	word = ft_strndup(&input[*i], len);
	new_node = init_lex(word, WORD, flag1, flag2);
	add_to_list(head, current, new_node);
	*i += len - 1;
	free(word);
}

void	handle_env(char *input, int *i, t_word **head, t_word **current)
{
	char	*word;
	int		j;
	t_word	*new_node;
	int		flag1;
	int		flag2;

	flag1 = check_space_before(input, i);
	flag2 = 0;
	while (input[*i] && input[*i] == '$')
	{
		j = *i + 1;
		while (input[j] && !is_space(input[j]) && input[j] != '"'
			&& input[j] != '\'' && input[j] != ';' && input[j] != '$')
			j++;
		if (j > *i + 1)
		{
			flag2 = check_space_after(input, j);
			word = ft_strndup(&input[*i + 1], j - *i - 1);
			new_node = init_lex(word, V_ENV, flag1, flag2);
			add_to_list(head, current, new_node);
			*i = j - 1;
			free(word);
		}
		*i += 1;
	}
}
