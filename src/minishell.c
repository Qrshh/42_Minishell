/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:04:34 by abesneux          #+#    #+#             */
/*   Updated: 2024/05/20 20:34:45 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
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
        clear_history();
    }
    return (0);
}