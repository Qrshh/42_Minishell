/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrshh <qrshh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:04:34 by abesneux          #+#    #+#             */
/*   Updated: 2024/05/27 19:30:48 by qrshh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int init_sh(t_all *all)
{
    char *temp;

    all->input = readline("MINISHELL $");
    temp = ft_strtrim(all->input, " ");
    free(all->input);
    all->input = temp;
    if(!all->input)
    {
        printf("exit");
        //free;
        exit(0);
    }
    if(all->input[0] == '\0')
        return(reset_all(all));
    add_history(all->input);
    reset_all(all);
    return(1);
}

int main(int ac, char **av, char **env)
{
    t_all *all;

    (void)av;
    (void)env;
    if(ac != 1)
        return (ft_printf("Error"), 1);
    all = malloc(sizeof(t_all));
    if(!all)
        return (ft_printf("Error while malloc"), 1);
    init_sh(all);
    return (0);
}
