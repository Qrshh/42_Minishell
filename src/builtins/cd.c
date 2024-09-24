/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:58:31 by qrshh             #+#    #+#             */
/*   Updated: 2024/09/24 13:07:38 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_cd(t_cmd *cmd)
{
	char	*home;

	if (!cmd->args[1])
	{
		home = getenv("HOME");
		if (!home)
			return (printf("cd: HOME not set\n"), 1);
		if (chdir(home) != 0)
			return (printf("cd: no such file or directory: %s\n", home), 1);
	}
	else
	{
		if (chdir(cmd->args[1]) != 0)
			return (printf("cd: no such file or directory: %s\n", cmd->args[1]), 1);
	}
	return (0);
}
