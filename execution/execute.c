/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:12:59 by mberthou          #+#    #+#             */
/*   Updated: 2025/06/17 16:01:17 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	child_process(t_obj *obj, int input_fd, int output_fd, int *pipe_fd)
{
	char	*cmd_path;

	if (obj->cmd->infile)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (obj->cmd->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
	if (obj->cmd->outfile)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
	/* if (is_built_in(obj->cmd)) */
	/* 	run_builtin(obj); */
	else
	{
		cmd_path = get_absolute_path(obj->cmd, obj->env);
		if (!cmd_path)
			return (127); // we should free everything and exit(127)
		if (execve(cmd_path, obj->cmd->argv, obj->env) < 0)
		{
			perror("mafiyashell"); // clear everything
			exit(126);
		}
	}
	return (obj->exit_code);
}

static int	execute_command(t_obj *obj, int i, int *input_fd)
{
	int				pipe_fd[2];
	int				output_fd;

	open_fd(obj->cmd, input_fd, &output_fd);
	if (obj->cmd->next)
	{
		if (pipe(pipe_fd) < 0)
				return (127);
	}
	obj->pid[i] = fork();
	if (obj->pid[i] == 0)
		child_process(obj, *input_fd, output_fd, pipe_fd);
	else if (obj->pid[i] < 0)
		return (127);
	else
	{
		if (obj->cmd->infile)
			close(*input_fd);
		if (obj->cmd->next)
		{
			close(pipe_fd[1]);
			*input_fd = pipe_fd[0];
		}
	}
	return (0);
}

static void	wait_for_all(int number_of_commands, int *pid)
{
	int	i;

	i = 0;
	while (i < number_of_commands)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

static void	execution_routine(t_obj *obj)
{
	int		i;
	int		number_of_commands;
	int		input_fd;
	t_cmd	*current;

	input_fd = STDIN_FILENO;
	current = obj->cmd;
	number_of_commands = 0;
	while (current)
	{
		number_of_commands++;
		current = current->next;
	}
	obj->pid = (int *)malloc(sizeof(int) * number_of_commands);
	if (!obj->pid)
		exit(127);
	i = -1;
	while (obj->cmd)
	{
		obj->exit_code = execute_command(obj, i++, &input_fd);
		obj->cmd = obj->cmd->next;
	}
	wait_for_all(number_of_commands, obj->pid);
}

void	execute(t_obj *obj)
{
	t_cmd	*current;
	/* int		save_stdin; */
	/* int		save_stdout; */
	/* int		infile; */
	/* int		outfile; */

	create_files(obj);
	current = obj->cmd;
	/* if (!current->next && is_built_in(current)) */
	/* { */
	/* 	save_stdin = dup(STDIN_FILENO); */
	/* 	save_stdout = dup(STDOUT_FILENO); */
	/* 	set_redirections(obj, &infile, &outfile); */
	/* 	run_builtin(obj, infile, outfile); */
	/* 	dup2(save_stdin, STDIN_FILENO); */
	/* 	dup2(save_stdout, STDOUT_FILENO); */
	/* 	close(save_stdin); */
	/* 	close(save_stdout); */
	/* 	close(infile); */
	/* 	close(outfile); */
	/* } */
	/* else */
		execution_routine(obj);
	free_cmd(obj->cmd);
	free(obj->input);
}
