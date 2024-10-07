/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:40:07 by ozdemir           #+#    #+#             */
/*   Updated: 2024/10/07 19:52:53 by abesneux         ###   ########.fr       */
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
		while (cmd->args[i][j] == 'n')
			j++;
		if (cmd->args[i][j] == '\0')
		{
			flag = 1;
			i++;
		}
		else
			break ;
	}
	return (flag);
}

int my_echo(t_cmd *cmd)
{
	t_word *current;
	int flag;

	current = cmd->list;
	current = current->next;
	flag = flag_check(cmd);
	if(flag)
		current = current->next;
	while(current)
	{
		if(current->token == WORD || current->token == V_ENV)
		{
			ft_printf("%s", current->str);
			if(current->next)
				ft_printf(" ");
		}
		else 
			break ;
		current = current->next;
	}
	if(!flag)
		ft_printf("\n");
	return(0);
}
