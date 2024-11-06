/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:40:07 by ozdemir           #+#    #+#             */
/*   Updated: 2024/11/06 17:43:32 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	flag_check(t_cmd *cmd)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	flag = 0;
	while (cmd->args[i] && cmd->args[i][0] == '-')
	{
		j = 1;
		while(cmd->args[i][j] == 'n')
			j++;
		if (cmd->args[i][j] == '\0')
		{
			flag++;
			i++;
		}
		else
			break ;
	}
	return (flag);
}

int	my_echo(t_cmd *cmd)
{
	t_word	*current;
	int		flag;
	int	i;

	i = 0;
	current = cmd->list;
	current = current->next;
	flag = flag_check(cmd);
	while (flag != 0 && i < flag)
	{
		current = current->next;
		i++;
	}
	while (current)
	{
		if (current->token == WORD || current->token == V_ENV)
		{
			printf("%s", current->str);
			if (current->next)
				printf(" ");
		}
		else
			break ;
		current = current->next;
	}
	if (!flag)
		printf("\n");
	return (0);
}
