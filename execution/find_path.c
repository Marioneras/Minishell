/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:14:32 by mberthou          #+#    #+#             */
/*   Updated: 2025/06/13 17:50:14 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_absolute_path(t_cmd *cmd, t_obj *obj)
{
	int		i;
	char	*exec;
	char	**paths;
	char	*path;

	if (cmd->argv[0][0] == '/')
		return (ft_strdup(cmd->argv[0]));
	
}
