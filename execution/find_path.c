/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:14:32 by mberthou          #+#    #+#             */
/*   Updated: 2025/06/17 16:04:54 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_variable(char **env, char *variable)
{
	int	i;
	int	variable_len;

	variable = ft_strjoin(variable, "=");
	if (!variable)
		return (NULL);
	variable_len = ft_strlen(variable);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], variable, variable_len) == 0)
			return (free(variable), &env[i][variable_len]);
		i++;
	}
	free(variable);
	return (NULL);
}

char	*get_absolute_path(t_cmd *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**paths;
	char	*path;

	if (!cmd->argv[0][0])
		return (NULL);
	if (cmd->argv[0][0] == '/' || ft_strncmp(cmd->argv[0], "./", 2) == 0)
		return (ft_strdup(cmd->argv[0]));
	paths = ft_split(get_env_variable(env, "PATH"), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
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
