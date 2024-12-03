/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/09/10 22:37:35 by abesneux          #+#    #+#             */
/*   Updated: 2024/11/18 17:01:06 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	my_exit(t_cmd *cmd, t_env *env)
{
	int	exit_code;

	if (cmd->args[1] && cmd->args[2])
		return (ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO), 1);
	if (!cmd->args[1])
		exit_code = 0;
	else if (cmd->args[1] && is_str_digit(cmd->args[1]))
		exit_code = ft_atoi(cmd->args[1]);
	else if (cmd->args[1][0] == '-' && is_str_digit(&cmd->args[1][1]))
		exit_code = 256 + ft_atoi(cmd->args[1]);
	else
		return (ft_putstr_fd("exit: numeric argument required\n",
				STDERR_FILENO), 2);
	free_cmd(cmd);
	free_tab(env->env_cpy);
	exit(exit_code);
}
