/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 00:53:43 by qrshh             #+#    #+#             */
/*   Updated: 2024/11/14 15:31:00 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(char *input)
{
	if (has_unclosed_quotes(input))
	{
		ft_putstr_fd("Syntax error : unclosed quotes \n", STDERR_FILENO);
		return (1);
	}
	else if (has_logical_operator(input))
	{
		ft_putstr_fd("Syntax error : logical operators are not supported \n",
			STDERR_FILENO);
		return (1);
	}
	else if (pipe_checker(input))
	{
		ft_putstr_fd("Syntax error : misplaced operator \n", STDERR_FILENO);
		return (1);
	}
	ft_strtrim(input, " \t");
	return (0);
}

int	has_unclosed_quotes(const char *input)
{
	int	i;
	int	quote_type;

	i = 0;
	quote_type = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (input[i - 1] != '\\')
			{
				if (quote_type == input[i])
					quote_type = 0;
				else if (!quote_type)
					quote_type = input[i];
			}
		}
		i++;
	}
	if (quote_type)
		return (1);
	return (0);
}

int	pipe_checker(const char *input)
{
	int	length;
	int	start;
	int	end;

	length = ft_strlen(input);
	start = 0;
	end = length - 1;
	while (start < length && is_space(input[start]))
		start++;
	while (end >= 0 && is_space(input[end]))
		end--;
	if (input[start] == '|' || input[end] == '|')
		return (1);
	return (0);
}

int	redir_checker(const char *input)
{
	int	length;
	int	start;
	int	end;

	length = ft_strlen(input);
	start = 0;
	end = length - 1;
	while (start < length && is_space(input[start]))
		start++;
	while (end >= 0 && is_space(input[end]))
		end--;
	if (input[start] == '<' || input[start] == '>' || input[end] == '<'
		|| input[end] == '>')
		return (1);
	return (0);
}

int	has_logical_operator(const char *in)
{
	int	i;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (in[i])
	{
		update_quotes_count(in[i], &s_quotes, &d_quotes);
		if (!(s_quotes % 2) && !(d_quotes % 2) && (((in[i] == '&') && (in[i
							+ 1] == '&')) || ((in[i] == '|') && (in[i
							+ 1] == '|'))))
			return (1);
		if (((in[i] == '<') && (in[i + 1] == '<') && (in[i + 2] == '<'))
			|| ((in[i] == '>') && (in[i + 1] == '>') && (in[i + 2] == '>')))
			return (1);
		i++;
	}
	return (0);
}
