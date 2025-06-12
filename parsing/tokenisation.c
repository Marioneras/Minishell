/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:34:57 by mberthou          #+#    #+#             */
/*   Updated: 2025/06/11 14:34:59 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	is_sep(char c, char *token, bool track_s_quote, bool track_d_quote)
{
	int	len;

	if (!token)
		return (false);
	len = ft_strlen(token);
	if (((c == 39 && track_s_quote) || (c == '"' && track_d_quote)) && token)
		return (true);
	if (track_s_quote || track_d_quote)
		return (false);
	if ((!track_s_quote && !track_d_quote)
		&& ((token[len - 1] == '"' && c == '"')
		|| (token[len - 1] == '\'' && c == '\'')))
		return (false);
	if ((!track_s_quote && !track_d_quote) && (token[len - 1] == '"' || token[len - 1] == '\''))
		return (true);
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
		str[1] = '\0';
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
	free((char *)src);
	return (str);
}

static void	validate_quotes(char c, bool *s_quote, bool *d_quote)
{
	if (c == '"' && (!*d_quote && !*s_quote))
		*d_quote = true;
	else if (c == 39 && (!*s_quote && !*d_quote))
		*s_quote = true;
	else if (c == '"' && *d_quote)
		*d_quote = false;
	else if (c == 39 && *s_quote)
		*s_quote = false;
}

static void	initialize_tolkien(t_token *new_token)
{
	new_token->type = 0;
	new_token->previous = NULL;
	new_token->next = NULL;
	new_token->name = NULL;
}

static t_token	*get_token(char **str)
{
	t_token	*new_token;
	bool	track_s_quote;
	bool	track_d_quote;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	initialize_tolkien(new_token);
	track_s_quote = false;
	track_d_quote = false;
	while (**str)
	{
		validate_quotes(**str, &track_s_quote, &track_d_quote);
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

static void	find_type(t_token *token)
{
	if (ft_strncmp(token->name, "\"\"", 3) == 0
		|| ft_strncmp(token->name, "''", 3) == 0)
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
	else if (!token->previous || token->previous->type == EMPTY)
		token->type = CMD;
	else if (token->previous->type == PIPE
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
