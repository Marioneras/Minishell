/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:57:35 by mberthou          #+#    #+#             */
/*   Updated: 2025/05/30 17:45:18 by mberthou         ###   ########.fr       */
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

/* static void	init_cmd(t_cmd *new_cmd) */
/* { */
/* 	new_cmd->argv = NULL; */
/* 	new_cmd->infile = NULL; */
/* 	new_cmd->outfile = NULL; */
/* 	new_cmd->append = false; */
/* 	new_cmd->heredoc = false; */
/* 	new_cmd->lexer = NULL; */
/* 	new_cmd->next = NULL; */
/* 	new_cmd->previous = NULL; */
/* } */
/**/
/* static t_cmd	*get_cmd(t_token *current) */
/* { */
/* 	t_cmd	*new_cmd; */
/* 	int		count_argv; */
/**/
/* 	new_cmd = (t_cmd *)malloc(sizeof(t_cmd)); */
/* 	if (!new_cmd) */
/* 		return (NULL); */
/* 	init_cmd(new_cmd); */
/* 	count_argv == 0; */
/* 	while (current) */
/* 	{ */
/* 		if (current->type == COMMAND || current->type == ARGUMENT) */
/* 			count_argv++; */
/* 		if (current->type == PIPE) */
/* 	} */
/* } */
/**/
/* static void	create_cmd(t_obj *obj) */
/* { */
/* 	t_token	*current; */
/* 	t_cmd	*head; */
/* 	t_cmd	*new_cmd; */
/**/
/* 	head = get_cmd(obj->token); */
/* 	if (!head) */
/* 		return (NULL); */
/* 	current = obj->token->next; */
/* 	while (current) */
/* 	{ */
/* 		new_cmd = get_cmd(current); */
/* 		if (!new_cmd) */
/* 			return (NULL); */
/* 		append_node(head, new_cmd); */
/* 		new_cmd = new_cmd->next; */
/* 	} */
/* } */

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
			print_list(obj->token);
		/* expand(obj->token); */
		/* create_cmd(obj); */
		free_token(obj->token);
	}
	else if (check_quotes(obj->input) == 0)
		quote_error(obj->input);
}
