/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:43:09 by abesneux          #+#    #+#             */
/*   Updated: 2024/08/09 21:52:19 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_word  *init_lex(char *str, t_token token)
{
    t_word  *node;
    int i = 0;

    node = malloc(sizeof(t_word));
    if(!node)
        return NULL;
    node->str = ft_strdup(str);
    node->token = token;
    node->index = i++;
    node->previous = NULL;
    node->next = NULL;
    return(node);
}