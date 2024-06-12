void    update_quotes_count(char c, int *s_quotes, int *d_quotes)
{
    if (c == 34)
        (*d_quotes) ++;
    else if (c == 39)
        (*s_quotes) ++;
}

int     is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}
