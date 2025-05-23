/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:06:30 by mberthou          #+#    #+#             */
/*   Updated: 2025/05/23 19:31:25 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		free(tmp->name);
		free(tmp);
		token = token->next;
	}
}
