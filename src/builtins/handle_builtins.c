/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:59:00 by ozdemir           #+#    #+#             */
/*   Updated: 2024/11/06 13:03:32 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_cmd *cmd, t_env *env)
{
	int	res;

	res = 1;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		res = my_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		res = my_cd(cmd, env);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		res = my_pwd();
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		res = my_export(cmd, env);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		res = my_unset(cmd, env);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		res = my_env(cmd, env);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		res = my_exit(cmd, env);
	return (res);
}

int	is_a_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else
		return (0);
}
