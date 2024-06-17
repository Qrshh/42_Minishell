#include "minishell.h"

void cut_input(const char *input)
{
    char **str;

    str = ft_split(input, ';');
    int i = 0;
    while(str[i])
    {
        ft_printf("%s\n", str[i]);
        i++;
    }
}