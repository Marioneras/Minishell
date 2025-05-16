/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:34:57 by mberthou          #+#    #+#             */
/*   Updated: 2025/05/16 17:15:23 by mberthou         ###   ########.fr       */
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
	}
	return (head);
}

static char	is_sep(char c, char *token, bool is_inside_quote)
{
	if (is_inside_quote == true || !token)
		return (false);
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (true);
	if ((c == '|' || c == '<' || c == '>')
	 && (*token != '|' || *token != '<' || *token != '>'))
		return (true);
	if ((c != '|' || c != '<' || c != '>')
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

static t_token	*get_token(char **str)
{
	t_token	*new_token;
	bool	is_inside_quote;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = 0;
	is_inside_quote = false;
	while (**str)
	{
		if (**str == '"' || **str == 39)
			is_inside_quote = true;
		if (is_sep(**str, new_token->name, is_inside_quote))
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

t_token	*tokenize(char *str)
{
	t_token	*head;
	t_token	*new_token;

	head = get_token(&str);
	if (!head)
		return (NULL);
	while (*str)
	{
		new_token = get_token(&str);
		if (!new_token)
			return (NULL);
		append_token(head, new_token);
		/* token_type(new_token); */
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
		if (current_node->type == CMD)
			printf("type: COMMANDE EXTERNE\n");
		else if (current_node->type == BUILD_IN)
			printf("type: BUILD-IN\n");
		else if (current_node->type == ARGUMENT)
			printf("type: ARGUMENT\n");
		else
			printf("type: OPERATOR\n");
		current_node = current_node->next;
	}
}

int main(int argc, char **argv)
{
	t_token	*list;

	(void)argc;
	list = tokenize(argv[1]);
	if (!list)
		exit(1);
	print_list(list);
	return (0);
}
