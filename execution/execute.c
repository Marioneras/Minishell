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

int	pipex(int input_fd, int output_fd, char *cmd, char **envp)
{
	int		pipefd[2];
	pid_t	pid;
	char	**args;
	char	*cmd_path;

	if (!prepare_command(cmd, envp, &args, &cmd_path) || pipe(pipefd) < 0)
		return (close(input_fd), ft_clear(&cmd_path), 127);
	pid = fork();
	if (pid == 0)
	{
		dup2(input_fd, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		close(input_fd);
		close(output_fd);
		if (execve(cmd_path, args, envp) < 0)
			return (perror("Pipex"), clean_command(args, cmd_path), 127);
	}
	else if (pid < 0)
		return (clean_command(args, cmd_path), 127);
	close(pipefd[1]);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	return (clean_command(args, cmd_path), pipefd[0]);
}

int	execute_last_cmd(int input_fd, int output_fd, char *cmd, char **envp)
{
	pid_t	pid;
	char	**args;
	char	*cmd_path;

	if (!prepare_command(cmd, envp, &args, &cmd_path))
		return (127);
	pid = fork();
	if (pid == 0)
	{
		dup2(input_fd, STDIN_FILENO);
		dup2(output_fd, STDOUT_FILENO);
		close(input_fd);
		close(output_fd);
		if (execve(cmd_path, args, envp) < 0)
		{
			clean_command(args, cmd_path);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		return (clean_command(args, cmd_path), EXIT_FAILURE);
	clean_command(args, cmd_path);
	return (0);
}

static void	open_fd(char *input, char *output, int *output_fd, int *pipe_fd)
{
	if (input)
	{
		pipe_fd = 
	}
}

static int	execution_routine(t_obj *obj)
{
	int	i;
	int	output_fd;
	int	pipe_fd;
	int	last_status;

	open_fd(ac, av, &output_fd, &pipe_fd);
	while (i < ac - 2)
		pipe_fd = pipex(pipe_fd, output_fd, av[i++], envp);
	if (output_fd != -1)
		last_status = execute_last_cmd(pipe_fd, output_fd, av[ac - 2], envp);
	if (pipe_fd)
		close(pipe_fd);
	close(output_fd);
	i = -1;
	while (i++ < ac - 2)
		wait(NULL);
	return (last_status);
}

/* static int	count_commands(t_cmd *cmd) */
/* { */
/* 	t_cmd	*current; */
/* 	int		count; */
/**/
/* 	current = cmd; */
/* 	count = 0; */
/* 	while (current) */
/* 	{ */
/* 		count++; */
/* 		current = current->next; */
/* 	} */
/* 	return (count); */
/* } */
/**/
/* static int	child_process(t_obj *obj, t_cmd *cmd, int pipe_fd) */
/* { */
/* 	char	*cmd_path; */
/**/
/* 	if (cmd->infile) */
/* 	{ */
/* 		dup2(cmd->infile, STDIN_FILENO); */
/* 		close(cmd->infile); */
/* 	} */
/* 	dup2(pipe_fd[1], STDOUT_FILENO); */
/* 	close(pipe_fd[1]); */
/* 	close(pipe_fd[0]); */
/* 	if (cmd->outfile) */
/* 		close(cmd->outfile); */
/* 	if (is_built_in(cmd)) */
/* 		run_builtin(cmd); */
/* 	else */
/* 	{ */
/* 		cmd_path = get_absolute_path(cmd, obj); */
/* 		if (!cmd_path) */
/* 			return (EXIT_FAILURE); */
/* 		if (execve(cmd_path, cmd->argv, obj->envp) < 0) */
/* 			perror("mafiyashell"); // clear everything */
/* 	} */
/* 	return (EXIT_SUCCESS); */
/* } */
/**/
/* static void	wait_for_all(int number_of_commands) */
/* { */
/* 	int	i; */
/**/
/* 	i = 0; */
/* 	while (i < number_of_commands) */
/* 	{ */
/* 		wait(NULL); */
/* 		i++; */
/* 	} */
/* } */
/**/
/* static void	execution_routine(t_obj *obj) */
/* { */
/* 	int		pipe_fd[2]; */
/* 	int		number_of_commands; */
/* 	int		i; */
/* 	t_cmd	*current; */
/**/
/* 	number_of_commands = count_commands(obj->cmd); */
/* 	obj->pid = (int *)malloc(sizeof(int) * number_of_commands); */
/* 	if (!obj->pid) */
/* 		return ; // stop everything */
/* 	current = obj->cmd; */
/* 	i = 0; */
/* 	while (current) */
/* 	{ */
/* 		if (pipe(pipe_fd) < 0) */
/* 			return (); // clear and return right exit code */
/* 		obj->pid[i] = fork(); */
/* 		if (obj->pid[i] == 0) */
/* 			child_process(obj, current, pipe_fd); */
/* 		else if (obj->pid[i] < 0) */
/* 			return ; // same */
/* 		close(pipe_fd[1]); */
/* 		current = current->next; */
/* 		i++; */
/* 	} */
/* 	wait_for_all(number_of_commands); */
/* } */

void	execute(t_obj *obj)
{
	t_cmd	*current;

	create_files(obj);
	current = obj->cmd;
	/* if (!current->next && is_built_in(current)) */
	/* { */
	/* 	set_redirections(obj); */
	/* 	(obj->exit_code = )run_builtin(obj); */
	/* } */
	/* else */
		execution_routine(obj);
	free_cmd(obj->cmd);
	free(obj->input);
}
