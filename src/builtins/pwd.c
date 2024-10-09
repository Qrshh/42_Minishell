/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:03:45 by qrshh             #+#    #+#             */
/*   Updated: 2024/10/09 17:08:04 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_pwd(t_cmd *cmd)
{
	char	cwd[PATH_MAX];

	if (cmd->args[1])
		return (ft_putstr_fd("pwd: too many arguments\n", STDERR_FILENO), 1);
	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	else
		return (1);
}
