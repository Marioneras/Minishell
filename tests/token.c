/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:01:01 by mberthou          #+#    #+#             */
/*   Updated: 2025/05/16 17:15:25 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	word_count(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str == ' '  || (*str >= '\t' && *str <= '\r'))
			str++;
		if (*str)
			count++;
		if (ft_isalpha(*str))
		{
			while (*str && ft_isalpha(*str))
				str++;
		}
		else
		{
			while (*str && !ft_isalpha(*str))
				str++;
		}
	}
	return (count);
}

t_token	*create_node(char *str)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->name = str;
	new_node->type = 0;
	new_node->next = NULL;
	return (new_node);
}

t_token	*insert_at_end(t_token *head, t_token *node)
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

t_token	*create_list(char **array, int number_of_words)
{
	t_token	*new_node;
	t_token	*head;
	int		i;

	i = 0;
	head = create_node(array[i]);
	if (!head)
		return (NULL);
	while (++i < number_of_words)
	{
		new_node = create_node(array[i]);
		if (!new_node)
			return (NULL);
		insert_at_end(head, new_node);
		new_node = new_node->next;
	}
	return (head);
}

char	*word_dup(char *str)
{
	char	*new_word;
	int		len;
	int		i;

	len = 0;
	if (ft_isalpha(*str) || *str == '-')
	{
		while (str[len] && ft_isalpha(str[len]))
			len++;
	}
	else
	{
		while (str[len] && !ft_isalpha(str[len]))
			len++;
	}
	new_word = (char *)malloc(sizeof(char) * len + 1);
	if (!new_word)
			return (NULL);
	i = -1;
	while (i++ < len)
		new_word[i] = str[i];
	new_word[len] = '\0';
	return (new_word);
}

char	**split_cmd(char *str, int number_of_words)
{
	char	**split_cmd;
	int		i;

	split_cmd = (char **)malloc(sizeof(char *) * number_of_words + 1);
	if (!split_cmd)
		return (NULL);
	i = 0;
	while (*str)
	{
		while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
			str++;
		if (*str)
		{
			split_cmd[i++] = word_dup(str);
			if (ft_isalpha(*str))
			{
				while (ft_isalpha(*str))
					str++;
			}
			else
			{
				while (!ft_isalpha(*str))
					str++;
			}
		}
	}
	split_cmd[number_of_words] = NULL;
	return (split_cmd);
}

t_token	*ft_strtok(char *str)
{
	char	**cmds;
	int		number_of_words;
	t_token	*head;

	number_of_words = word_count(str);
	cmds = split_cmd(str, number_of_words);
	if (!cmds)
		return (NULL);
	head = create_list(cmds, number_of_words);
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

int	main(int argc, char **argv)
{
	t_token	*list;

	(void)argc;
	list = ft_strtok(argv[1]);
	if (!list)
		exit(1);
	print_list(list);
	return (0);
}
