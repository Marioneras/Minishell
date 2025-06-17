/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:57:01 by mberthou          #+#    #+#             */
/*   Updated: 2025/06/17 10:07:53 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_built_in(t_cmd *cmd)
{
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		return (true);
	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		return (true);
	if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		return (true);
	if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		return (true);
	if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		return (true);
	if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		return (true);
	if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		return (true);
	return (false);
}

int	run_builtin(t_obj obj)
{
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		run_echo();
	else if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		run_cd();
	else if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		run_pwd();
	else if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		run_export();
	else if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		run_unset();
	else if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		run_env();
	else if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		run_exit();
	return (0);
}
