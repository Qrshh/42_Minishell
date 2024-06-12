
#include "minishell.h"

int check_syntax(const char *input)
{
    if(has_unclosed_quotes(input))
    {
        ft_putstr_fd("Syntax error : unclosed quotes \n", STDERR_FILENO);
        return(1);
    }
    return (0);
}

int     has_unclosed_quotes(const char *input)
{
    int     i;
    int     quote_type;

    i = 0;
    quote_type = 0;
    while(input[i])
    {
        if(input[i] == '\'' || input[i] == '\"')
        {
            if(quote_type == input[i])
                quote_type = 0;
            else if (!quote_type)
                quote_type = input[i];
        }
        i++;
    }
    if(quote_type)
        return(1);
    return(0);
}
