/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:12:28 by ozdemir           #+#    #+#             */
/*   Updated: 2024/10/09 17:13:07 by ozdemir          ###   ########.fr       */
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
	cmd->old_out = dup(STDOUT_FILENO);
	cmd->old_inf = dup(STDIN_FILENO);
	return (cmd);
}
