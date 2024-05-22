/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrshh <qrshh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:04:34 by abesneux          #+#    #+#             */
/*   Updated: 2024/05/22 20:26:56 by qrshh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **env)
{
    t_global *global;

    (void)av;
    (void)env;
    if(ac != 1)
        return (ft_printf("Error"), 1);
    global = malloc(sizeof(t_global));
    if(!global)
        return (ft_printf("Error while malloc"), 1);
    char *command;
    while(1)
    {
        command = readline("Prompt> ");

        if(command == NULL)
            command = readline("Prompt> ");
        if(ft_strlen(command) > 0)
            add_history(command);
        if(ft_strcmp(command, "exit") == 0)
        {
            free(command);
            clear_history();
            break;
        }
        free(command);
    }
    return (0);
}
