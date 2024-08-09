/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:25:33 by abesneux          #+#    #+#             */
/*   Updated: 2024/08/09 21:55:36 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handle_operator(char *input, int *i, t_word **current, char operator)
{
    t_token token;
    char *temp;
    int len;

    len = 1;
    if(operator == '|')
        token = PIPE;
    else if ((operator == '>' || operator == '<') && input[*i + 1])
    {
        len = 2;
        if(operator == '<')
            token == DOUBLE_LEFT;
        else if (operator == '>')
            token == DOUBLE_RIGHT;
    }
    else if (operator == '<')
        token = LEFT;
    else if (operator == '>')
        token = RIGHT;
    //JE DOIS INITIALISER QQ CHOSE POUR REGROUPER ENSUITE LES TOKENS DES OPERATORS
    temp = ft_strndup(&input[*i], len);
    *current = init_lex(temp, token);
    free(temp);
}

void    handle_single_quote(char *input, int *i, t_word **current, char quote)
{
    char *word;
    int j;

    j = *i + 1;
    while(input[j] && input[j] != quote)
        j++;
    if(input[j] == quote)
    {
        word = ft_strndup(&input[*i + 1], j -  *i - 1); //copie le mot de i +1 jusqu'a avant j (quote)
        *current = init_lex(word, WORD);
        *i = j;
        free(word);
    }
}
