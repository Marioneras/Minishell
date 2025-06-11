#include "minishell.h"

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	int		i;
	int		j;

	current = cmd;
	i = 1;
	while (current)
	{
		printf("------------------------\n");
		printf("Commande %d :\n", i);
		printf("argv = [");
		j = 0;
		while (current->argv[j])
		{
			if (current->argv[j + 1])
				printf("%s, ", current->argv[j]);
			else
				printf("%s", current->argv[j]);
			j++;
		}
		printf("]\n");
		if (current->infile)
		{
			printf("infile = \"%s\"\n", current->infile);
			printf("heredoc = %s\n", current->heredoc ? "true" : "false");
		}
		if (current->outfile)
		{
			printf("outfile = \"%s\"\n", current->outfile);
			printf("append = %s\n", current->append ? "true" : "false");
		}
		i++;
		current = current->next;
	}
	printf("------------------------\n");
}

void	print_list(t_token *list)
{
	t_token	*current_node;

	current_node = list;
	while (current_node)
	{
		printf("------------------------\n");
		printf("%s\n", current_node->name);
		if (current_node->type == EMPTY)
			printf("type: EMPTY\n");
		else if (current_node->type == CMD)
			printf("type: COMMANDE\n");
		else if (current_node->type == ARGUMENT)
			printf("type: ARGUMENT\n");
		else if (current_node->type == PIPE)
			printf("type: PIPE\n");
		else if (current_node->type == TRUNC)
			printf("type: TRUNC\n");
		else if (current_node->type == INPUT)
			printf("type: INPUT\n");
		else if (current_node->type == APPEND)
			printf("type: APPEND\n");
		else if (current_node->type == HEREDOC)
			printf("type: HEREDOC\n");
		else if (current_node->type == LIMITER)
			printf("type: LIMITER\n");
		else if (current_node->type == FD)
			printf("type: FILE\n");
		current_node = current_node->next;
	}
}
