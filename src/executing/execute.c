/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/07/08 22:06:12 by abesneux          #+#    #+#             */
/*   Updated: 2024/11/20 17:42:32 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*path_join(char *path, char *bin, t_arena *arena)
{
	char	*joined;
	int		i;
	int		j;

	joined = arena_alloc(arena, sizeof(char) * (ft_strchr(path, 0)
				+ ft_strchr(bin, 0) + 2));
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

char	*getpath(char *cmd, char **env, t_arena *arena)
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
		dir = aft_strndup(path, ft_strchr(path, ':'), arena);
		bin = path_join(dir, cmd, arena);
		if (access(bin, F_OK) == 0)
			return (bin);
		path += ft_strchr(path, ':') + 1;
	}
	return (cmd);
}

void	exec(t_cmd *cmd, t_env *env, t_arena *arena)
{
	char	*path;

	path = getpath(cmd->args[0], env->env_cpy, arena);
	if (!path || execve(path, cmd->args, env->env_cpy) == -1)
	{
		printf("Command not found\n");
		exit(127);
	}
}

void	process_pipe(t_cmd *cmd, t_env *env, t_arena *arena)
{
	pid_t	*pids;
	int		i;

	pids = arena_alloc(arena, (cmd->nb_pipes + 1) * sizeof(pid_t));
	if (!pids)
		return ;
	i = 0;
	while (cmd->nb_pipes >= 0)
	{
		if (handle_single_pipe(cmd, env, &pids[i], arena) < 0)
			return ;
		cmd->args = cmd->post_pipe;
		cmd->nb_pipes--;
		i++;
	}
	wait_children(pids, i);
}

void	execute_command(t_cmd *cmd, t_env *env, t_arena *arena)
{
	char	*path;

	if (cmd->args[0] == NULL)
		return ;
	path = getpath(cmd->args[0], env->env_cpy, arena);
	if (cmd && cmd->nb_pipes > 0)
		process_pipe(cmd, env, arena);
	else
		simple_exec(cmd, env, path, arena);
	signal(SIGQUIT, SIG_IGN);
}
