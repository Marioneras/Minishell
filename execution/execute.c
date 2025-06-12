/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:12:59 by mberthou          #+#    #+#             */
/*   Updated: 2025/06/12 23:48:18 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_commands(t_cmd *cmd)
{
	t_cmd	*current;
	int		count;

	current = cmd;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}



static void	execution_routine(t_obj *obj)
{
	int		pipe_fd[2];
	int		number_of_commands;
	int		i;
	t_cmd	*current;
	char	*cmd_path;

	number_of_commands = count_commands(obj->cmd);
	obj->pid = (int *)malloc(sizeof(int) * number_of_commands);
	if (!obj->pid)
		return ; // stop everything
	current = obj->cmd;
	i = 0;
	while (current)
	{
		if (!prepare_command(obj, &cmd_path) || pipe(pipe_fd) < 0)
			return (); // clear and return right exit code
		obj->pid[i] = fork();
		if (obj->pid[i] == 0)
			child_process();
		else if (obj->pid[i] < 0)
			return ; // same
		close(pipe_fd[1]);
		current = current->next;
		i++;
	}
}

void	execute(t_obj *obj)
{
	t_cmd	*current;

	current = obj->cmd;
	if (!current->next && is_built_in(current))
	{
		set_redirections(obj);
		run_builtin(obj);
	}
	else
		execution_routine(obj);
	free_cmd(obj->cmd);
	free(obj->input);
}
