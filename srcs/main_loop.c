/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <safamran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:36:22 by mberthou          #+#    #+#             */
/*   Updated: 2025/06/19 13:53:56 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ctrl_c(int signal, siginfo_t *info, void *contex)
{
	(void)signal;
	(void)info;
	(void)contex;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void init_signal()
{
	struct sigaction sa;
	sa.sa_sigaction = ctrl_c;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

static void init_obj(t_obj *obj)
{
	obj->token = NULL;
	obj->cmd = NULL;
	obj->env = NULL;
	obj->tool = (t_tool *)malloc(sizeof(t_tool));
	if (!obj->tool)
		exit(2);
	if (getcwd(obj->tool->pwd, sizeof(obj->tool->pwd)) == NULL)
	{
		perror("getcwd() error");
		free(obj->tool);
		exit(2);
	}
	if (getcwd(obj->tool->old_pwd, sizeof(obj->tool->pwd)) == NULL)
	{
		perror("getcwd() error");
		free(obj->tool);
		exit(2);
	}
	obj->input = NULL;
	obj->pid = 0;
	obj->exit_code = 0;
}

int main(int argc, char *argv[], char **envp)
{
	t_obj obj;

	(void)argv;
	(void)envp;
	init_obj(&obj);
	if (argc == 1)
	{
		init_signal();
		clear_history();
		while (1)
		{
			init_signal();
			obj.input = readline("mafiyashell> "); // readline renvoie str alloue (=ce que user a ecrit)
			if (ft_strncmp(obj.input, "exit", 5) == 0)
			{
				// free_obj(obj);
				exit(0); // + free machin
			}
			add_history(obj.input);
			parsing(&obj, envp);
			// execute(&obj);
		}
	}
	return (obj.exit_code);
}
