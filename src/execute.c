/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:36:36 by qrshh             #+#    #+#             */
/*   Updated: 2024/05/29 14:11:18 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*path_join(char *path, char *bin)
{
	char	*joined;
	int		i;
	int		j;

	joined = malloc(sizeof(char) * (ft_strchr(path, 0) + ft_strchr(bin, 0)
				+ 2));
	i = 0;
	j = 0;
	while (path[j])
	{
		joined[i] = path[j];
		i++;
		j++;
	}
	joined[i] = '/';
	i++;
	j = 0;
	while (bin[j])
	{
		joined[i] = bin[j];
		i++;
		j++;
	}
	joined[i] = 0;
	return (joined);
}

char	*getpath(char *cmd, char **env)
{
	char	*path;
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (cmd);
	path = env[i] + 5;
	while (path && ft_strchr(path, ':') > -1)
	{
		dir = ft_strndup(path, ft_strchr(path, ':'));
		bin = path_join(dir, cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += ft_strchr(path, ':') + 1;
	}
	return (cmd);
}

void	execute_command(char *cmd, char **env)
{
	char	**args;
	char	*path;
	int		i;
	pid_t	pid;
	int		status;

	i = -1;
	if (*cmd == '\0')
	{
		printf("Erreur: commande vide\n");
		return ;
	}
	args = ft_split(cmd, ' ');
	if (ft_strchr(args[0], '/') > -1)
		path = args[0];
	else
		path = getpath(args[0], env);
	pid = fork();
	if (pid == 0) /*Processus enfant */
	{
		if (execve(path, args, env) == -1)
		{
			perror("Erreur d'exécution");
			while (args[++i])
				free(args[i]);
			free(args);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0) /*Erreur de fork */
		perror("Erreur de fork");
	else                          /*Processus parent */
		waitpid(pid, &status, 0);
			/*Attendre que le processus enfant se termine */
	while (args[++i])
		free(args[i]);
	free(args);
}
