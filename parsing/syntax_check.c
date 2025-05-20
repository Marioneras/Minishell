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

int	check_pipe(t_token *current)
{
	if (!current->previous || !current->next)
		return (1);
}

int	check_redirections(t_token *current)
{
	if (current->type == HEREDOC && !current->next)
		return (1);
	if (current->type == HEREDOC && (current->next->type == HEREDOC
		|| current->previous->type == HEREDOC))
		return (1);
	if (current->next->type == PIPE)
		return (1);
}

int	check_fd(t_token *current)
{

}

bool	check_syntax(t_token *head)
{
	t_token	*current;
	int		result;

	if (!head)
		return (false);
	current = head;
	result = 0;
	while (current)
	{
		/* if (current->type == EMPTY) */
			/* result += check_empty(); */
		if (current->type == PIPE)
			result += check_pipe(current);
		else if ((current->type == TRUNC) || (current->type == APPEND)
		   || (current->type == INPUT) || (current->type == HEREDOC))
			result += check_redirections(current);
		else if (current->type == FD)
			result += check_fd(current);
		current = current->next;
	}
	if (result != 0)
		return (false);
	return (true);
}
