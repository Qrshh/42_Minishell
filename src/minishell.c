/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrshh <qrshh@student.42.fr>                +#+  +:+       +#+           */
/*   Created: 2024/05/20 20:04:34 by abesneux          #+#    #+#             */
/*   Updated: 2024/05/27 19:30:48 by qrshh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>


int init_sh(t_all *all, char **env)
{
    char *temp;

    all->input = readline("MINISHELL $ ");
    if (!all->input)
    {
        printf("exit\n");
        exit(0);
    }
    temp = ft_strtrim(all->input, " ");
    free(all->input);
    all->input = temp;
    if (all->input[0] == '\0')
    {
        reset_all(all);
        return 0;
    }
    add_history(all->input);
    execute_command(all->input, env);
    reset_all(all);
    return (1);
}


int main(int ac, char **av, char **env)
{
    t_all *all;

    (void)av;
    if (ac != 1)
    {
        printf("Error: Too many arguments\n");
        return 1;
    }

    all = malloc(sizeof(t_all));
    if (!all)
    {
        printf("Error while malloc\n");
        return 1;
    }

    while (1)
    {
        if (!init_sh(all, env))
            continue;
    }

    free(all);
    return (0);
}
