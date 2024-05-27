/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrshh <qrshh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:06:36 by abesneux          #+#    #+#             */
/*   Updated: 2024/05/27 19:26:36 by qrshh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "Libft/inc/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_all
{
    char *input;
}t_all;

//INTIALISATION
int init_sh(t_all *all);

//ALL FUNCTIONS
int reset_all(t_all *all);
void init_all(t_all *all);

#endif