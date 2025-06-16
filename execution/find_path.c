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

char	*get_env_variable(t_env *env, char *variable)
{
	t_env	*current;
	int		variable_len;

	variable_len = ft_strlen(variable);
	current = env;
	while (current)
	{
		if (ft_strncmp(current->key, variable, variable_len) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*get_absolute_path(t_cmd *cmd, t_obj *obj)
{
	int		i;
	char	*exec;
	char	**paths;
	char	*path;

	if (!cmd->argv[0][0])
		return (NULL);
	if (cmd->argv[0][0] == '/')
		return (ft_strdup(cmd->argv[0]));
	paths = ft_split(get_env_variable(obj->env, PATH), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], '/');
		if (!path)
			return (NULL);
		exec = ft_strjoin(path, cmd->argv[0]);
		free(path);
		if (!exec)
			return (NULL);
		if (access(exec, F_OK | X_OK) == 0)
			return (ft_clear_tab(paths), exec);
		free(exec);
		i++;
	}
	ft_clear_tab(paths);
	ft_putstr_fd("mafiyashell: command not find\n", 2);
	return (NULL);
}
