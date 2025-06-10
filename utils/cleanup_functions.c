/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <safamran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:06:30 by mberthou          #+#    #+#             */
/*   Updated: 2025/06/10 18:46:57 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_list(t_token *token)
{
	t_token *tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp)
			free(tmp);
	}
}
