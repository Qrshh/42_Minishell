/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:06:12 by abesneux          #+#    #+#             */
/*   Updated: 2024/10/22 22:31:55 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **main_env)
{
	int		i;
	int		len;
	char	**str;

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

void	exec(t_cmd *cmd, t_env *env)
{
	char	*path;

	if (is_a_builtin(cmd->args[0]))
	{
		g_exit_status = execute_builtin(cmd, env);
		return ;
	}
	else
	{
		path = getpath(cmd->args[0], env->env_cpy);
		execve(path, cmd->args, env->env_cpy);
	}
}

void	process_pipe(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	pid_t	pid2;
	int		pipefd[2];

	if (pipe(pipefd) < 0)
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		if (is_a_builtin(cmd->args[0]))
		{
			g_exit_status = execute_builtin(cmd, env);
			exit(g_exit_status);
		}
		else
			exec(cmd, env);
	}
	pid2 = fork();
	if (pid2 < 0)
		return ;
	if (pid2 == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		cmd->args = cmd->post_pipe;
		if (is_a_builtin(cmd->args[0]))
		{
			g_exit_status = execute_builtin(cmd, env);
			exit(g_exit_status);
		}
		else
			exec(cmd, env);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}
void	execute_command(t_cmd *cmd, t_env *env)
{
	char	*path;
	pid_t	pid;
	int		status;

	if (cmd->args[0] == NULL)
		return ;

	path = getpath(cmd->args[0], env->env_cpy);
	if(cmd->flag_pipe)
		process_pipe(cmd, env);
	else 
	{
		if (is_a_builtin(cmd->args[0]))
		{
			g_exit_status = execute_builtin(cmd, env);
			return ;
		}
		pid = fork();
		if (pid == 0)
		{
			execve(path, cmd->args, env->env_cpy);
			perror("Erreur d'exécution");
			exit(127);
		}
		else if (pid < 0)
			perror("Erreur de fork");
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else
				g_exit_status = 128 + WTERMSIG(status);
		}
	}

}
