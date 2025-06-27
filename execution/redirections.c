/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:07:26 by mberthou          #+#    #+#             */
/*   Updated: 2025/06/17 16:05:42 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file(char *filename, int type)
{
	int	fd;

	if (type == INPUT)
		fd = open(filename, O_RDONLY);
	else if (type == TRUNC)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		printf("mafiyashell: %s: %s\n", filename, strerror(errno));
	return (fd);
}

void	open_fd(t_cmd *cmd, int *input_fd, int *output_fd)
{
	/* if (cmd->infile && cmd->heredoc) */
	/* 	*input_fd = here_doc(); */
	if ((cmd->infile && cmd->infile == STDIN_FILENO) && !cmd->heredoc)
		*input_fd = open(cmd->infile, O_RDONLY);
	if (cmd->outfile && cmd->append)
		*output_fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (cmd->outfile && !cmd->append)
		*output_fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*input_fd < 0)
		printf("mafiyashell: %s: %s\n", cmd->infile, strerror(errno));
	if (*output_fd < 0)
		printf("mafiyashell: %s: %s\n", cmd->outfile, strerror(errno));
}

void	create_files(t_obj *obj)
{
	t_cmd	*current;

	current = obj->cmd;
	while (current->next)
	{
		/* if (current->infile && heredoc) */
			/* here_doc(); */
		if (current->infile && !current->heredoc)
			open_file(current->infile, INPUT);
		if (current->outfile && current->append)
			open_file(current->outfile, APPEND);
		else if (current->outfile && !current->append)
			open_file(current->outfile, TRUNC);
		current = current->next;
	}
}

void	set_redirections(t_obj *obj, int *infile, int *outfile)
{
	if (obj->cmd->infile)
	{
		/* if (obj->cmd->here_doc) */
			/* *infile = here_doc(); */
		*infile = open(obj->cmd->infile, O_RDONLY);
		if (*infile < 0)
			exit (127);
		if (dup2(*infile, STDIN_FILENO) < 0)
			printf("mafiyashell: %s: %s\n", obj->cmd->infile, strerror(errno));
	}
	if (obj->cmd->outfile)
	{
		if (obj->cmd->append)
			*outfile = open(obj->cmd->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			*outfile = open(obj->cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (*outfile < 0)
			exit(127);
		if (dup2(*outfile, STDOUT_FILENO) < 0)
			printf("mafiyashell: %s: %s\n", obj->cmd->outfile, strerror(errno));
	}
}

/* still need to exit in case the files cannot be opened */
