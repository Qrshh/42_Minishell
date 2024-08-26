/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:03:45 by qrshh             #+#    #+#             */
/*   Updated: 2024/08/26 12:43:19 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_all *all)
{
	free(all->pwd);
	all->pwd = getcwd(NULL, 1024);
	printf("%s\n", all->pwd);
	return (0);
}
