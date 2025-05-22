/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:09:05 by mberthou          #+#    #+#             */
/*   Updated: 2025/05/22 18:15:53 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_error(char *str)
{
	free(str);
	write(1, "Error\n", 7);
	rl_replace_line("", 0);
	rl_on_new_line();
	//rl_redisplay();
}

int	in_double(char **str)
{
	(*str)++;
	while(**str != '\0')
	{
		if (**str == 34)
		{
			//(*str)++;
			return (1);
		}
		(*str)++;
	}
	return (0);
}

int	in_single(char **str)
{
	(*str)++;
	while(**str != '\0')
	{
		if (**str == 39)
		{
			//(*str)++;
			return(1);
		}
		(*str)++;
	}
	return (0);
}

int	is_there_quote(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while(str[i] != '\0')
	{
		if (str[i] == 34 || str[i] == 39)
			count ++;
		i++;
	}
	if (count == 0)
		return (0);
	return(1);
}

int	check_quotes(char *str)
{
	int	result;

	result = -1;
	if (is_there_quote(str) == 0)
		return (1);
	while(*str != '\0')
	{
		if (result == 0)
			return (0);
		if (*str == 34)
			result = in_double(&str);
		if (result == 0)
			return (0);
		if (*str == 39)
			result = in_single(&str);
		if (*str != 39 || *str != 34)
			str++;
	}
	//if (quote % 2 == 0 && double_quote % 2 == 0)
	//	return(1);
	//else
	//	return(0);
		//return(Q_ERROR(127))
	if (result == 0)
		return (0);
	else
		return (1);
}
/*
int main(int argc, char *argv[])
{
        if (argc > 1)
        {
                if (check_quotes(argv[1]) == 1)
                        printf("TRUE");
                if (check_quotes(argv[1]) == 0)
                        printf("FALSE");
        }
        return(0);
}*/
