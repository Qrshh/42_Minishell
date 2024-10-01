/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:39:13 by ozdemir           #+#    #+#             */
/*   Updated: 2024/10/01 19:13:28 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char *ft_strstr(const char *str1, const char *str2) // $USER USER
{
    size_t i;
    size_t j;

    if (!*str2)
    {
        ft_printf("on est teuber ? \n");
        return (char *)str1;
    }
    i = 0;
    while (str1[i] != '\0')
    {
        if (str1[i] == str2[0])
        {
            j = 0;
            while (str2[j] != '\0')
            {
                if (str1[i + j] != str2[j])
                    break;
                j++;
            }
            if (str2[j] == '\0')
                return (char *)&str1[i];
        }
        i++;
    }
    return NULL;
}
