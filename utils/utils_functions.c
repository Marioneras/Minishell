/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <safamran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:22:17 by safamran          #+#    #+#             */
/*   Updated: 2025/06/09 17:34:56 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *special_case(char *str, int *i)
{
    (void)*i;
    if (*str == '$')
    {
        str++;
        return(ft_itoa(getpid()));
    }

    if (*str == '?')
    {
        str++;
       // return(ft_itoa(last_exit_code));
    }

    if (check_char(*str) == 0)
        return ("$");
    return (NULL);
}

int     check_char(char c)
{
    if (c >= 'A' && c <= 'Z')
        return (1);
    if (c >= 'a' && c <= 'z')
        return (1);
    if (c >= '0' && c <= '9')
        return (1);
    if (c == '_')
        return (1);
    return (0);
}

char    *join_and_free(char *s1, char *s2)
{
    char *result;

    result = ft_strjoin(s1, s2);
    free(s1);
    return (result);
}
