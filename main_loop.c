#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void	ctrl_c(int signal, siginfo_t *info, void *contex)
{
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
	(void)argv;
	(void)envp;

	char	*command; // a free
	if (argc == 1)
	{
		init_signal();
		clear_history();
		while (1)
		{
			init_signal();
			if (strcmp(command, "exit") == 0)
				exit (0); // + free machin
			command = readline("mafiyashell> "); //readline renvoie str alloue (=ce que user a ecrit)
			if (check_quotes(command) == 1)
				printf("TRUE\n");
			if (check_quotes(command) == 0)
				quote_error(command);
				//printf("FALSE\n");
			//if(parse_it(command) == 0)
			//	error_free;
			add_history(command);
		}
	}
	return(0);
}
/*
int	parse_it(char *str)
{
	int	i;

	i = 0;

	if (check_quotes == 0)
		return(0)
	if (marion == 0)
		return (0)
	return(1);
}
*/
