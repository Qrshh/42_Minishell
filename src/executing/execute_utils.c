/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 21:04:49 by abesneux          #+#    #+#             */
/*   Updated: 2024/08/14 22:39:37 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     check_cmd(char *word, char **env)
{
	char *path;
	
    path = getpath(word, env);
    if (path && access(path, X_OK) == 0) // Vérifie si c'est exécutable
    {
    	printf("La commande '%s' est exécutable.\n", word);
		return (1);
        execute_command(word, env);
    }
    else
    {
        printf("Commande non trouvée ou non exécutable: '%s'\n", word);
		return(0);
    }
    if (path != word) // Libère la mémoire allouée dynamiquement
		free(path);
	return(0);
}

void pre_execute(t_word *list, char **env)
{
    t_word *current;  current = list;
    while (current)
    {
        if (current->token == 0) // Vérifie si le token correspond à une commande
		{
			if(check_cmd(current->str, env))
				execute_command(current->str, env);
        }
        current = current->next;
    }
}

