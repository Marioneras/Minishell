/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:36:22 by mberthou          #+#    #+#             */
/*   Updated: 2025/05/22 19:01:51 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int signal, siginfo_t *info, void *contex)
{
	(void)signal;
	(void)info;
	(void)contex;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	init_signal()
{
	struct	sigaction	sa;
	sa.sa_sigaction = ctrl_c;
	sa.sa_flags = SA_SIGINFO;
	sigaction (SIGINT, &sa, NULL);
}

int	main(int argc, char *argv[], char **envp)
{
	t_token	*token_list;
	char	*command; // a free
	int		exit_code;

	(void)argv;
	(void)envp;
	if (argc == 1)
	{
		init_signal();
		clear_history();
		while (1)
		{
			init_signal();
			command = readline("mafiyashell> "); //readline renvoie str alloue (=ce que user a ecrit)
			if (strcmp(command, "exit") == 0)
				exit (0); // + free machin
			add_history(command);
			exit_code = 0;
			if (check_quotes(command) == 1)
			{
				token_list = tokenize(command);
				exit_code = check_syntax(token_list);
				if (exit_code == PIPE_ERROR)
					return (printf("minishell: syntax error near unexpected token `|`\n"), 2);
				else if (exit_code == MISSING_FILENAME)
					return(printf("minishell: syntax error near unexpected token `newline`\n"), 2);
				else if (exit_code == INVALID_OPERATOR)
					return (printf("minishell: syntax error near unexpected token `>>`\n"), 2);
				else
					print_list(token_list);
			}
			else if (check_quotes(command) == 0)
				quote_error(command);
				//printf("FALSE\n");
			//if(parse_it(command) == 0)
			//	error_free;
		}
	}
	return(0);
}
/*
int	parse_it(char *str)
{
	int	i;

	exit_code = 0;

	if (check_quotes == 0)
		return(0)
	if (marion == 0)
		return (0)
	return(1);
}
*/
