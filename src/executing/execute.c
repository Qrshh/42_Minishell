/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:06:12 by abesneux          #+#    #+#             */
/*   Updated: 2024/09/25 16:31:55 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **main_env)
{
	int	i;
	int len;
	char **str;

	i = -1;
	len = 0;
	while (main_env[len])
		len++;
	str = malloc(sizeof(char *) * (len + 1));
	if (!str)
		return (NULL);
	while (++i < len)
	{
		str[i] = ft_strdup(main_env[i]);
		if (!str[i])
		{
			while (i > 0)
				free(str[--i]);
			free(str);
			return (NULL);
		}
	}
	str[len] = NULL;
	return (str);
}

char	*path_join(char *path, char *bin)
{
	char	*joined;
	int		i;
	int		j;

	joined = malloc(sizeof(char) * (ft_strchr(path, 0) + ft_strchr(bin, 0)
				+ 2));
	i = -1;
	j = -1;
	while (path[++j])
		joined[++i] = path[j];
	joined[++i] = '/';
	j = -1;
	while (bin[++j])
		joined[++i] = bin[j];
	joined[++i] = 0;
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

void	execute_command(t_cmd *cmd, t_env *env)
{
	char	*path;
	pid_t	pid;
	int		status;

	if (cmd->args[0] == NULL)
		return ;
	if (is_a_builtin(cmd->args[0]))
	{
		g_exit_status = execute_builtin(cmd, env);
		return ;
	}
	path = getpath(cmd->args[0], env->env_cpy);
	pid = fork();
	if (pid == 0)
	{
		execve(path, cmd->args, env->env_cpy);
		perror("Erreur d'exécution");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror("Erreur de fork");
	else
	{
		waitpid(pid, &status, 0);
	}
}
