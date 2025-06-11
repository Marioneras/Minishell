/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:03:24 by mberthou          #+#    #+#             */
/*   Updated: 2025/06/11 14:40:15 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirections	*append_redirections(t_redirections *head, t_redirections *node)
{
	t_redirections	*current_node;

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

t_cmd	*append_cmd(t_cmd *head, t_cmd *node)
{
	t_cmd	*current_node;

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

t_token	*append_token(t_token *head, t_token *node)
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
