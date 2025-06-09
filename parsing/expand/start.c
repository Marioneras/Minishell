/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <safamran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:22:11 by safamran          #+#    #+#             */
/*   Updated: 2025/06/09 17:34:55 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int nb_dollar(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '$')
            return (1);
        i++;
    }
    return (0);
}

int quote_check(char *str)
{
    int i;

    i = 0;
    // if (nb_quote(str) == 0)
    //   return (0);
    if (str[i] == 34)
        return (1);
    if (str[i] == 39)
        return (0);
    return (0);
}

int nb_quote(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '"' || str[i] == '\'')
            return (1);
        i++;
    }
    return (0);
}

int is_expand(char *str)
{
    if (nb_dollar(str) == 0)
        return (0);
    if (nb_quote(str) != 0)
    {
        if (quote_check(str) == 0)
        {
            printf("\n%s\n\n", str);
            printf("\nhere\n");
            return (0);
        }
    }
    return (1);
}
