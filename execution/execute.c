/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:12:59 by mberthou          #+#    #+#             */
/*   Updated: 2025/06/13 17:50:16 by mberthou         ###   ########.fr       */
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

static void	child_process(t_obj *obj, t_cmd *cmd, int pipe_fd)
{
	char	*cmd_path;

	dup2(cmd->infile, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	close(cmd->infile);
	close(cmd->outfile);
	if (is_built_in(cmd))
		run_builtin(cmd);
	else
	{
		cmd_path = get_absolute_path();
		if (execve(cmd_path, cmd->argv, obj->envp) < 0)
			perror("mafiyashell"); // clear everything
	}
}

static void	wait_for_all(int number_of_commands)
{
	int	i;

	i = 0;
	while (i < number_of_commands)
	{
		wait(NULL);
		i++;
	}
}

static void	execution_routine(t_obj *obj)
{
	int		pipe_fd[2];
	int		number_of_commands;
	int		i;
	t_cmd	*current;

	number_of_commands = count_commands(obj->cmd);
	obj->pid = (int *)malloc(sizeof(int) * number_of_commands);
	if (!obj->pid)
		return ; // stop everything
	current = obj->cmd;
	i = 0;
	while (current)
	{
		if (pipe(pipe_fd) < 0)
			return (); // clear and return right exit code
		obj->pid[i] = fork();
		if (obj->pid[i] == 0)
			child_process(obj, current, pipe_fd);
		else if (obj->pid[i] < 0)
			return ; // same
		close(pipe_fd[1]);
		current = current->next;
		i++;
	}
	wait_for_all(number_of_commands);
}

void	execute(t_obj *obj)
{
	t_cmd	*current;

	current = obj->cmd;
	/* create_files(); */
	/* if (!current->next && is_built_in(current)) */
	/* { */
	/* 	set_redirections(obj); */
	/* 	run_builtin(obj); */
	/* } */
	/* else */
		execution_routine(obj);
	free_cmd(obj->cmd);
	free(obj->input);
}
