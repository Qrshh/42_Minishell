/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:37:35 by abesneux          #+#    #+#             */
/*   Updated: 2024/09/11 14:47:14 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	my_exit(t_cmd *cmd)
{
	int	exit_code;

	if (cmd->args[1] && cmd->args[2])
		return (ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO), 1);
	if (!cmd->args[1])
		exit_code = 0;
	else if (cmd->args[1] && is_str_digit(cmd->args[1]))
		exit_code = ft_atoi(cmd->args[1]);
	else
	{
		ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
		exit_code = 2;
	}
	exit(exit_code);
}
