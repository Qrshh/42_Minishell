/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:39:06 by ozdemir           #+#    #+#             */
/*   Updated: 2024/10/01 19:38:44 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	var_name = ft_substr(str, 0, i);
	return (var_name);
}

char	*replace_var(char *input, char *var_name, char *var_value)
{
	int		i;
	int		new_len;
	char	*new_input;
	char	*pos;

	i = 0;
	new_input = malloc(sizeof(char) * (ft_strlen(var_value) + 1));
	if (!new_input)
		return (NULL);
	// pos = ft_strstr(input, var_name);
	pos = ft_strstr(var_name,input);
	// printf("ft_strstr :%s\n", pos);
	if (pos)
	// {
		ft_strncpy(new_input, var_value, ft_strlen(var_value)+1);
		// new_input[pos - input] = '\0';
		// ft_strcat(new_input, var_value);
		// ft_strcat(new_input, pos + strlen(var_name));
	// }
	// printf("laaaa --new_input:%s\n", new_input);
	free(input);
	return (new_input);
}

char	*find_var_value(t_env *env, char *var_name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var_name);
	while (env->env_cpy[i])
	{
		if (ft_strncmp(env->env_cpy[i], var_name, len) == 0
			&& env->env_cpy[i][len] == '=')
			return (&env->env_cpy[i][len + 1]);
		i++;
	}
	return (NULL);
}

t_word *handle_dollar(t_all *all, t_env *env)
{
    t_word *current;
    char *var_value;
    char *var_name; 
    char *dollar_var_name;

    current = all->list;
    while (current)
    {
        if (current->token == V_ENV) // Si le token est de type ENV
        {
            var_name = get_var_name(current->str); // Obtenir le nom de la variable
            dollar_var_name = ft_strjoin("$", var_name); // Construire le nom avec le dollar
            var_value = find_var_value(env, var_name); // Trouver la valeur
            if (var_value)
			{
                current->str = replace_var(current->str, dollar_var_name, var_value);
				free(dollar_var_name); 
			}
            else
                current->str = replace_var(current->str, dollar_var_name, "");
			free(var_name);
        }
		current = current->next;
    }
    return all->list;
}

