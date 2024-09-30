/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:39:06 by ozdemir           #+#    #+#             */
/*   Updated: 2024/09/30 22:09:50 by abesneux         ###   ########.fr       */
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
	new_len = ft_strlen(input) - ft_strlen(var_name) + ft_strlen(var_value);
	new_input = malloc(sizeof(char) * new_len + 1);
	if (!new_input)
		return (NULL);
	pos = ft_strstr(input, var_name);
	if (pos)
	{
		ft_strncpy(new_input, input, pos - input);
		new_input[pos - input] = '\0';
		ft_strcat(new_input, var_value);
		ft_strcat(new_input, pos + strlen(var_name));
	}
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
    t_word *current; // Pointeur sur la liste de tokens
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

            // Si une valeur est trouvée, remplacer le contenu du token
            if (var_value)
            {
                // Libérer l'ancienne chaîne 
                // Allouer et copier la nouvelle valeur
                current->str = replace_var(current->str, dollar_var_name, var_value); 
            }
            else
            {
                // Si aucune valeur n'est trouvée, on peut choisir de laisser le token tel quel
                // ou de le remplacer par une chaîne vide, à définir selon votre logique.
                current->str = ft_strdup(dollar_var_name); // Remplacer par $VAR sans valeur
            }

            // Libération de la mémoire utilisée pour le nom de la variable et le dollar_var_name
            free(var_name);
            free(dollar_var_name);
        }
        current = current->next; // Passer au token suivant
    }
    return all->list; // Retourner la liste des tokens modifiée
}

