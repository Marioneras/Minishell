/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:36:59 by mberthou          #+#    #+#             */
/*   Updated: 2025/05/20 19:52:59 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_pipe(t_token *current)
{
	if (!current->previous || !current->next)
		return (false);
	if (current->previous->type == PIPE || current->next->type == PIPE)
		return (false);
	return (true);
}

char	*check_redirection(t_token *current)
{
	if (current->previous)
	{
			if (current->previous->type == TRUNC
			|| current->previous->type == APPEND
			|| current->previous->type == INPUT
			|| current->previous->type == HEREDOC)
			return (current->name);
	}
	return ("OK");
}

int	redirection_error(char *str)
{
	ft_putstr_fd("mafiyashell: syntax error near unexpected token `", 2);
	if(ft_strlen(str) >= 2)
	{
		ft_putchar_fd(*str, 2);
		ft_putchar_fd(*str, 2);
	}
	else
		ft_putchar_fd(*str, 2);
	ft_putstr_fd("'\n", 2);
	return (INVALID_OPERATOR);
}

int	check_syntax(t_token *head)
{
	t_token	*current;

	if (!head)
		return (false);
	current = head;
	while (current)
	{
		if (current->type == PIPE && !check_pipe(current))
			return (PIPE_ERROR);
		if (current->name[0] == '|' && current->type != PIPE)
			return (PIPE_ERROR);
		if ((current->type == TRUNC || current->type == APPEND
			|| current->type == INPUT || current->type == HEREDOC)
			&& ft_strncmp(check_redirection(current), "OK", 3) != 0)
			return (redirection_error(check_redirection(current)));
		if ((current->name[0] == '<' && (current->type != INPUT
			&& current->type != HEREDOC)) || (current->name[0] == '>'
			&& (current->type != TRUNC && current->type != APPEND)))
			return (redirection_error(current->name));
		if ((current->type == TRUNC || current->type == APPEND
			|| current->type == INPUT || current->type == HEREDOC)
			&& !current->next)
			 return (MISSING_FILENAME);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
