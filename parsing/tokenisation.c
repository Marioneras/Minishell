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

static char	is_sep(char	prev_c, char c, bool is_inside_quote)
{
	if (is_inside_quote)
		return (false);
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (true);
	if ((c == '|' || c == '<' || c == '>')
	 && !(prev_c == '|' || prev_c == '<' || prev_c == '>'))
		return (true);
	else
		return (false);
}

static t_token	*get_token(char **str)
{
	t_token	*new_token;
	bool	is_inside_quote;
	int		len;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	len = 0;
	is_inside_quote = false;
	while (**str)
	{
		if (**str == '"' || **str == "'")
			is_inside_quote = true;
		if (is_sep(**str, **str - 1, is_inside_quote))
		{
			while (**str == ' ' || (**str >= '\t' && **str <= '\r'))
				*str++;
			break;
		}
		len++;
		*str++;
	}
	new_token->name = (char *)malloc(sizeof(char) * len + 1);
	if (!new_token->name)
		return (NULL);
	ft_strlcpy(&new_token->name, str[0], len);
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
		token_type(new_token);
		new_token = new_token->next;
	}
	return (head);
}
