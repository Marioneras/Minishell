/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:57:35 by mberthou          #+#    #+#             */
/*   Updated: 2025/06/11 14:45:11 by mberthou         ###   ########.fr       */
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


static t_redirections	*get_redirection(t_token *current)
{
	t_redirections	*new_red;

	new_red = (t_redirections *)malloc(sizeof(t_redirections));
	if (!new_red)
		return (NULL);
	new_red->name = ft_strdup(current->next->name);
	if (!new_red->name)
		return (NULL);
	if (current->type == INPUT)
		new_red->type = INPUT;
	else if (current->type == APPEND)
		new_red->type = APPEND;
	else if (current->type == TRUNC)
		new_red->type = TRUNC;
	else if (current->type == HEREDOC)
		new_red->type = HEREDOC;
	return (new_red);
}

t_redirections	*handle_redirections(t_token *token)
{
	t_token			*current;
	t_redirections	*head;
	t_redirections	*new_red;

	current = token;
	while (current && (current->type != INPUT && current->type != APPEND
		&& current->type != TRUNC && current->type != HEREDOC))
		current = current->next;
	if (!current)
		return (NULL);
	head = get_redirection(current);
	if (!head)
		return (NULL);
	current = current->next;
	while (current && current->type != PIPE)
	{
		if (current->type == INPUT || current->type == APPEND
		|| current->type == TRUNC || current->type == HEREDOC)
		{
			new_red = get_redirection(current);
			if (!new_red)
				return (NULL);
			append_redirections(head, new_red);
			new_red = new_red->next;
		}
		current = current->next;
	}
	return (head);
}

static void	racine_ex(t_token *head, char **envp)
{
	t_token	*current;
	char	*result;

	current = head;
	while (current)
	{
		result = expand_it(current->name, envp);
		if (result)
		{
			free(current->name);
			current->name = ft_strdup(result);
		}
		current = current->next;
	}
}

void	parsing(t_obj *obj, char **envp)
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
			racine_ex(obj->token, envp);
			obj->cmd = create_cmd(obj);
			/* print_cmd(obj->cmd); */
		}
		free_token(obj->token);
	}
	else if (check_quotes(obj->input) == 0)
		quote_error(obj->input);
}
