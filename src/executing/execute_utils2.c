/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:12:28 by ozdemir           #+#    #+#             */
/*   Updated: 2024/11/12 20:30:05 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	count_pipes(t_word *list)
{
	int	count;

	count = 0;
	while (list)
	{
		if (list->token == PIPE)
			count++;
		list = list->next;
	}
	return (count);
}

t_cmd	*init_cmd(t_cmd *cmd, t_word *list)
{
	cmd->list = list;
	cmd->args = list_to_array(list);
	cmd->post_pipe = NULL;
	cmd->nb_pipes = 0;
	cmd->previous = NULL;
	cmd->old_out = dup(STDOUT_FILENO);
	cmd->old_inf = dup(STDIN_FILENO);
	return (cmd);
}
