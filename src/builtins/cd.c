/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:58:31 by qrshh             #+#    #+#             */
/*   Updated: 2024/09/09 19:32:38 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_cd(char **args)
{
	if (!args[1])
	{
		write(STDERR_FILENO, "Usage: cd <path>\n", 16);
		return ;
	}
	if (chdir(args[1]) != 0)
	{
		perror("cd");
	}
}
