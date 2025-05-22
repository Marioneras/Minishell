/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:34:57 by mberthou          #+#    #+#             */
/*   Updated: 2025/05/20 19:53:07 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*append_token(t_token *head, t_token *node)
{
	t_token	*current_node;

	if (!node)
		return (NULL);
	if (!head)
		head = node;
	else
	{
		current_node = head;
		while (current_node->next)
			current_node = current_node->next;
		current_node->next = node;
		node->previous = current_node;
	}
	return (head);
}

static char	is_sep(char c, char *token, bool track_s_quote, bool track_d_quote)
{
	if ((track_s_quote == true || track_d_quote) || !token)
		return (false);
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (true);
	if ((c == '|' || c == '<' || c == '>')
	 && (*token != '|' && *token != '<' && *token != '>'))
		return (true);
	if ((c != '|' && c != '<' && c != '>')
	 && (*token == '|' || *token == '<' || *token == '>'))
		return (true);
	else
		return (false);
}

static char	*str_append(char const *src, char c)
{
	char	*str;
	int		i;

	if (!c)
		return (NULL);
	if (!src)
	{
		str = (char *)malloc(sizeof(char) + 1);
		if (!str)
			return (NULL);
		*str = c;
		return (str);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(src) + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i++] = c;
	str[i] = '\0';
	return (str);
}

static void	check_quotes(char c, bool *s_quote, bool *d_quote)
{
	if (c == '"' && !*d_quote)
		*d_quote = true;
	else if (c == 39 && !*s_quote)
		*s_quote = true;
	else if (c == '"' && *d_quote)
		*d_quote = false;
	else if (c == 39 && *s_quote)
		*s_quote = false;
}

static t_token	*get_token(char **str)
{
	t_token	*new_token;
	bool	track_s_quote;
	bool	track_d_quote;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = 0;
	track_s_quote = false;
	track_d_quote = false;
	while (**str)
	{
		check_quotes(**str, &track_s_quote, &track_d_quote);
		if (is_sep(**str, new_token->name, track_s_quote, track_d_quote))
		{
			while (**str == ' ' || (**str >= '\t' && **str <= '\r'))
				(*str)++;
			break;
		}
		new_token->name = str_append(new_token->name, **str);
		(*str)++;
	}
	return (new_token);
}

void	find_type(t_token *token)
{
	if (!token->name)
		token->type = EMPTY;
	else if (ft_strncmp(token->name, "|", 2) == 0)
		token->type = PIPE;
	else if (ft_strncmp(token->name, ">", 2) == 0)
		token->type = TRUNC;
	else if (ft_strncmp(token->name, "<", 2) == 0)
		token->type = INPUT;
	else if (ft_strncmp(token->name, ">>", 3) == 0)
		token->type = APPEND;
	else if (ft_strncmp(token->name, "<<", 3) == 0)
		token->type = HEREDOC;
	else if (!token->previous || token->previous->type == PIPE
		|| token->previous->type == FD)
		token->type = CMD;
	else if (token->previous->type == HEREDOC)
		token->type = LIMITER;
	else if (token->previous->type == TRUNC || token->previous->type == APPEND
		|| token->previous->type == INPUT)
		token->type = FD;
	else
		token->type = ARGUMENT;
}

t_token	*tokenize(char *str)
{
	t_token	*head;
	t_token	*new_token;

	head = get_token(&str);
	find_type(head);
	if (!head)
		return (NULL);
	while (*str)
	{
		new_token = get_token(&str);
		if (!new_token)
			return (NULL);
		append_token(head, new_token);
		find_type(new_token);
		new_token = new_token->next;
	}
	return (head);
}

void	print_list(t_token *list)
{
	t_token	*current_node;

	current_node = list;
	while (current_node)
	{
		printf("------------------------\n");
		printf("%s\n", current_node->name);
		if (current_node->type == EMPTY)
			printf("type: EMPTY\n");
		else if (current_node->type == CMD)
			printf("type: COMMANDE\n");
		else if (current_node->type == ARGUMENT)
			printf("type: ARGUMENT\n");
		else if (current_node->type == PIPE)
			printf("type: PIPE\n");
		else if (current_node->type == TRUNC)
			printf("type: TRUNC\n");
		else if (current_node->type == INPUT)
			printf("type: INPUT\n");
		else if (current_node->type == APPEND)
			printf("type: APPEND\n");
		else if (current_node->type == HEREDOC)
			printf("type: HEREDOC\n");
		else if (current_node->type == LIMITER)
			printf("type: LIMITER\n");
		else if (current_node->type == FD)
			printf("type: FILE\n");
		current_node = current_node->next;
	}
}

int main(int argc, char **argv)
{
	t_token	*list;
	int		i;

	(void)argc;
	list = tokenize(argv[1]);
	if (!list)
		exit(1);
	i = 0;
	i = check_syntax(list);
	if (i == PIPE_ERROR)
		return (printf("minishell: syntax error near unexpected token `|`\n"), 2);
	else if (i == MISSING_FILENAME)
		return(printf("minishell: syntax error near unexpected token `newline`\n"), 2);
	else if (i == INVALID_OPERATOR)
		return (2);
	else
		print_list(list);
	return (0);
}
