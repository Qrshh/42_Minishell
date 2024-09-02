/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:40:07 by ozdemir           #+#    #+#             */
/*   Updated: 2024/09/02 17:05:47 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    my_echo(char **args)
{
        int     i;
        int     flag;

        i = 0;
        flag = 0;
        while (args[i])
        {
                if (ft_strcmp(args[i], "-n") == 0)
                        flag = 1;
                else
                        ft_printf("%s ", args[i]);
                i++;
        }
        if (!flag)
                ft_printf("\n");
}