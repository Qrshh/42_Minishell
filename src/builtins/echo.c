/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:40:07 by ozdemir           #+#    #+#             */
/*   Updated: 2024/09/25 16:32:40 by ozdemir          ###   ########.fr       */
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
int	my_echo(t_cmd *cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = flag_check(cmd);
	if (flag == 1)
		i = 2;
	while (cmd->args[i])
	{
		ft_printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!flag)
		ft_printf("\n");
	return (0);
}
