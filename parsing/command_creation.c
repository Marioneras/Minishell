/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <safamran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:50:19 by mberthou          #+#    #+#             */
/*   Updated: 2025/06/19 14:00:28 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int count_arguments(t_token *node)
{
	t_token *current;
	int count;

	current = node;
	count = 0;
	while (current && current->type != PIPE)
	{
		if (current->type == CMD || current->type == ARGUMENT)
			count++;
		current = current->next;
	}
	return (count);
}

static void init_cmd(t_cmd *new_cmd, t_token *token)
{
	int count;

	count = count_arguments(token);
	new_cmd->argv = (char **)malloc(sizeof(char *) * (count + 1));
	new_cmd->redirections = handle_redirections(token);
	if (!new_cmd->argv)
		return;
	new_cmd->outfile = NULL;
	new_cmd->infile = NULL;
	while (token && token->type != PIPE)
	{
		if (token->type == INPUT)
		{
			if (new_cmd->infile)
				free(new_cmd->infile);
			new_cmd->infile = ft_strdup(token->next->name);
			new_cmd->heredoc = false;
		}
		else if (token->type == HEREDOC)
		{
			if (new_cmd->infile)
				free(new_cmd->infile);
			new_cmd->infile = ft_strdup(token->next->name);
			new_cmd->heredoc = true;
		}
		else if (token->type == TRUNC)
		{
			if (new_cmd->outfile)
				free(new_cmd->outfile);
			new_cmd->outfile = ft_strdup(token->next->name);
			new_cmd->append = false;
		}
		else if (token->type == APPEND)
		{
			if (new_cmd->outfile)
				free(new_cmd->outfile);
			new_cmd->outfile = ft_strdup(token->next->name);
			new_cmd->append = true;
		}
		token = token->next;
	}
	new_cmd->next = NULL;
	new_cmd->previous = NULL;
}

static t_cmd *get_cmd(t_token **current)
{
	t_cmd *new_cmd;
	int i;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	init_cmd(new_cmd, (*current));
	i = 0;
	while ((*current) && (*current)->type != PIPE)
	{
		if ((*current)->type == CMD || (*current)->type == ARGUMENT)
		{
			new_cmd->argv[i] = ft_strdup((*current)->name);
			if (!new_cmd->argv[i])
				return (NULL);
			i++;
		}
		(*current) = (*current)->next;
	}
	new_cmd->argv[i] = NULL;
	return (new_cmd);
}

t_cmd *create_cmd(t_obj *obj)
{
	t_token *current;
	t_cmd *head;
	t_cmd *new_cmd;

	current = obj->token;
	head = get_cmd(&current);
	if (!head)
		return (NULL);
	while (current)
	{
		current = current->next;
		new_cmd = get_cmd(&current);
		if (!new_cmd)
			return (NULL);
		append_cmd(head, new_cmd);
		new_cmd = new_cmd->next;
	}
	return (head);
}
