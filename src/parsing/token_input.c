/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:13:13 by abesneux          #+#    #+#             */
/*   Updated: 2024/07/24 19:56:40 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_token **tokens, int *token_count, const char *value,
		TokenType type)
{
	printf("\n%d, %s\n", *token_count, value);
	*tokens = realloc(*tokens, (*token_count + 1) * sizeof(t_token));
	if (!*tokens)
	{
		perror("Error while reallocating tokens");
		exit(EXIT_FAILURE);
	}
	(*tokens)[*token_count].value = ft_strdup(value);
	(*tokens)[*token_count].type = type;
	(*token_count)++;
}

TokenType	identify_token(const char *input, int *length)
{
	if (*input == '|')
	{
		*length = 1;
		return (TOKEN_PIPE);
	}
	else if (ft_isalnum(*input))
	{
		*length = 0;
		while (input[*length] && input[*length] != ' ' && input[*length] != '|'
			&& input[*length] != '"')
			(*length)++;
		return (TOKEN_COMMAND);
	}
	else if (*input == '"')
		return (TOKEN_DOUBLE_QUOTES);
	else if (*input == '-')
	{
		*length = 0;
		while (input[*length] && input[*length] != ' ' && input[*length] != '|'
			&& input[*length] != '"')
			(*length)++;
		return (TOKEN_OPTION);
	}
	*length = 1;
	return (TOKEN_UNKNOWN);
}

void	tokenize(t_all *all, t_token **tokens)
{
	int			i;
	int			length;
	int			token_count;
	TokenType	type;

	i = 0;
	token_count = 0;
	*tokens = NULL;
	while (all->input[i])
	{
		if (all->input[i] == '\0')
			break ;
		if (all->input[i] == ' ' || all->input[i] == '"')
			i++;
		type = identify_token(&all->input[i], &length);
		add_token(tokens, &token_count, ft_strndup(&all->input[i], length),
			type);
		i += length;
	}
    for (int i = 0; i < token_count; i++)
	{
		printf("Token %d: %s Type: %d\n", i, (*tokens)[i].value,
			(*tokens)[i].type);
		free((*tokens)[i].value);
	}
	free(*tokens);
}
