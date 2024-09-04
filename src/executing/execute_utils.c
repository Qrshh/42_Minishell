/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 21:04:49 by abesneux          #+#    #+#             */
/*   Updated: 2024/09/04 15:27:40 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd(char *word, char **env)
{
	char	*path;

	path = getpath(word, env);
	if (path && access(path, X_OK) == 0)
	{
		ft_printf("La commande '%s' est exécutable.\n", word);
		return (1);
	}
	else
	{
		ft_printf("Commande non trouvée ou non exécutable: '%s'\n", word);
		return (0);
	}
	if (path != word)
		free(path);
	return (0);
}

void	pre_execute(t_word *list, char **env)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		perror("Erreur d'allocation mémoire pour cmd");
		return ;
	}
	cmd->list = list;
	cmd->args = list_to_array(list);
	cmd->pipe = NULL;
	cmd->previous = NULL;
	if (list->token == 0)
	{
		execute_command(cmd, env);
	}
	if (cmd->args)
	{
		for (int i = 0; cmd->args[i] != NULL; i++)
		{
			free(cmd->args[i]);
		}
		free(cmd->args);
	}
	free(cmd);
}

char	**list_to_array(t_word *list)
{
	int		count;
	t_word	*temp;
	char	**array;
	int		i;

	count = 0;
	temp = list;
	while (temp && ft_strcmp(temp->str, "|") != 0)
	{
		count++;
		temp = temp->next;
	}
	array = malloc((count + 1) * sizeof(char *));
	if (!array)
	{
		perror("Erreur d'allocation mémoire");
		return (NULL);
	}
	i = 0;
	while (list && ft_strcmp(list->str, "|") != 0)
	{
		array[i] = ft_strdup(list->str);
		if (!array[i])
		{
			perror("Erreur d'allocation mémoire");
			while (i > 0)
			{
				free(array[--i]);
			}
			free(array);
			return (NULL);
		}
		i++;
		list = list->next;
	}
	array[i] = NULL;
	return (array);
}
