/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrshh <qrshh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:04:34 by abesneux          #+#    #+#             */
/*   Updated: 2024/05/21 19:17:14 by qrshh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void exec(char *cmd, char **env)
{
    char **args;
    char *path;
    int i;

    i = -1;
    if(*cmd == '\0')
        exit_error("Erreur");
    args = ft_split(cmd, ' ');
    if(ft_strchr(args[0], '/') > -1)
        path = args[0];
    else 
        path = getpath(args[0], env);
    execve(path, args, env);
    while(args[++i])
        free(args[i]);
    free(args);
    exit_error("Command not found");
}

int main(int ac, char **av, char **env)
{
    t_global *global;

    (void)av;
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
        exec(command, env);
        if(ft_strlen(command) > 0)
            add_history(command);
        free(command);
    }
    return (0);
}
