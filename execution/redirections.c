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
		open(filename, O_RDONLY);
	else if (type == TRUNC)
		open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == APPEND)
		open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		printf("mafiyashell: %s: %s\n", filename, strerror(errno));
	return (fd);
}



void	create_files(t_obj *obj)
{
	t_cmd	*current;

	current = obj->cmd;
	while (current)
	{
		if (current->infile && heredoc)
			here_doc();
		else if (current->infile && !heredoc)
			open_file(current->infile, INPUT);
		if (current->output && append)
			open_file(current->output, APPEND);
		else if (current->output && !append)
			open_file(current->output, TRUNC);
		current = current->next;
	}
}

void	set_redirections(t_obj *obj)
{
	if (obj->cmd->infile)
	{
		if (dup2(obj->cmd->infile, STDIN_FILENO) < 0)
			printf("mafiyashell: %s: %s\n", obj->cmd->infile, strerror(errno));
	}
	if (obj->cmd->outfile)
	{
		if (dup2(obj->cmd->outfile, STDOUT_FILENO) < 0)
			printf("mafiyashell: %s: %s\n", obj->cmd->outfile, strerror(errno));
	}
}

/* still need to exit in case the files cannot be opened */
