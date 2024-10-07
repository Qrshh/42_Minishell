/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 21:04:49 by abesneux          #+#    #+#             */
/*   Updated: 2024/10/07 19:35:15 by abesneux         ###   ########.fr       */
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

t_cmd	*init_cmd(t_cmd *cmd, t_word *list)
{
	cmd->list = list;
	cmd->args = list_to_array(list);
	cmd->pipe = NULL;
	cmd->previous = NULL;
	cmd->old_fd = dup(STDOUT_FILENO);
	return (cmd);
}

void	pre_execute(t_word *list, t_env *env)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		perror("Erreur d'allocation mémoire pour cmd");
		return ;
	}
	init_cmd(cmd, list);
	if(handle_operator_exec(cmd->list))
	{
		dup2(cmd->old_fd, STDOUT_FILENO);
		close(cmd->old_fd);
		free(cmd);
		return ;
	}
	if (list->token == 0)
	{
		execute_command(cmd, env);
	}
	dup2(cmd->old_fd, STDOUT_FILENO);
	close(cmd->old_fd);
	if (cmd->args)
	{
		while (cmd->args[i] != NULL)
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	free(cmd);
}

int	count_list(t_word *list)
{
	int		count;
	t_word	*temp;

	count = 0;
	temp = list;
	while (temp && ft_strcmp(temp->str, "|") != 0)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

char	**list_to_array(t_word *list)
{
	char	**array;
	int		i;

	array = malloc((count_list(list) + 1) * sizeof(char *));
	if (!array)
	{
		perror("Erreur d'allocation mémoire");
		return (NULL);
	}
	i = 0;
	while (list && ft_strcmp(list->str, "|") != 0)
	{
		array[i] = ft_strdup(list->str);
		if (!array[i++])
		{
			perror("Erreur d'allocation mémoire");
			while (i > 0)
				free(array[--i]);
			free(array);
			return (NULL);
		}
		list = list->next;
	}
	array[i] = NULL;
	return (array);
}
