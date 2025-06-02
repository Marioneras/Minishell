/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:57:35 by mberthou          #+#    #+#             */
/*   Updated: 2025/05/31 16:39:54 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_only_space(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while(str[i] != '\0')
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return(1);
}

static void	just_enter(void)
{
	//write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	//rl_redisplay();
}

static void	init_cmd(t_cmd *new_cmd)
{
	new_cmd->argv = NULL;
	new_cmd->infile = NULL;
	new_cmd->outfile = NULL;
	new_cmd->append = false;
	new_cmd->heredoc = false;
	new_cmd->lexer = NULL;
	new_cmd->next = NULL;
	new_cmd->previous = NULL;
}

static int	count_arguments(t_token *node)
{
	t_token	*current;
	int		count;

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

/* static void	handle_redirections() */
/* { */
/**/
/* } */

static t_cmd	*get_cmd(t_token **current)
{
	t_cmd	*new_cmd;
	int		count;
	int		i;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	init_cmd(new_cmd);
	count = count_arguments((*current));
	new_cmd->argv = (char **)malloc(sizeof(char *) * count + 1);
	if (!new_cmd)
		return (NULL);
	i = 0;
	while ((*current))
	{
		if ((*current)->type == CMD || (*current)->type == ARGUMENT)
		{
			new_cmd->argv[i] = ft_strdup((*current)->name);
			if (!new_cmd->argv[i])
				return (NULL);
			i++;
		}
		else if ((*current)->type == INPUT)
		{
			new_cmd->infile = ft_strdup((*current)->next->name);
			if (!new_cmd->infile)
				return (NULL);
		}
		else if ((*current)->type == TRUNC || (*current)->type == APPEND)
		{
			new_cmd->outfile = ft_strdup((*current)->next->name);
			if (!new_cmd->outfile)
				return (NULL);
		}
		else if ((*current)->type == PIPE)
		{
			(*current) = (*current)->next;
			break;
		}
		if ((*current)->type == APPEND)
			new_cmd->append = true;
		else if ((*current)->type == HEREDOC)
			new_cmd->heredoc = true;
		(*current) = (*current)->next;
	}
	new_cmd->argv[i] = NULL;
	return (new_cmd);
}

static t_cmd	*create_cmd(t_obj *obj)
{
	t_token	*current;
	t_cmd	*head;
	t_cmd	*new_cmd;

	current = obj->token;
	head = get_cmd(&current);
	if (!head)
		return (NULL);
	while (current)
	{
		new_cmd = get_cmd(&current);
		if (!new_cmd)
			return (NULL);
		append_cmd(head, new_cmd);
		new_cmd = new_cmd->next;
	}
	return (head);
}

void	parsing(t_obj *obj)
{
	int	syntax_error;

	if (is_only_space(obj->input) == 1)
		just_enter();
	else if (check_quotes(obj->input) == 1)
	{
		obj->token = tokenize(obj->input);
		syntax_error = check_syntax(obj->token);
		if (syntax_error == PIPE_ERROR)
			printf("mafiyashell: syntax error near unexpected token `|'\n");
		else if (syntax_error == MISSING_FILENAME)
			printf("mafiyashell: syntax error near unexpected token `newline'\n");
		else if (syntax_error != INVALID_OPERATOR)
		{
			/* print_list(obj->token); */
			/* expand(obj->token); */
			obj->cmd = create_cmd(obj);
			print_cmd(obj->cmd);
		}
		free_token(obj->token);
	}
	else if (check_quotes(obj->input) == 0)
		quote_error(obj->input);
}
