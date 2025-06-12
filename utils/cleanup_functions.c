/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:06:30 by mberthou          #+#    #+#             */
/*   Updated: 2025/06/11 14:43:02 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->name);
		free(tmp);
	}
}

void	free_redirections(t_redirections *red)
{
	t_redirections	*tmp;

	while (red)
	{
		tmp = red;
		red = red->next;
		free(red->name);
		free(tmp);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int	i;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		i = 0;
		while (tmp->argv[i])
		{
			free(tmp->argv[i]);
			i++;
		}
		free(tmp->argv);
		if (tmp->infile)
			free(tmp->infile);
		if (tmp->outfile)
			free(tmp->outfile);
		free_redirections(tmp->redirections);
		free(tmp);
	}
}

/* void	free_obj(t_obj *obj) */
/* { */
/**/
/* } */
