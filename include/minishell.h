/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:43:33 by mberthou          #+#    #+#             */
/*   Updated: 2025/05/31 16:05:29 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

#define PATH_MAX        4096

typedef struct s_token
{
	char			*name;
	int				type;
	struct s_token	*next;
	struct s_token	*previous;
}					t_token;

typedef enum e_type
{
	CMD,
	ARGUMENT,
	PIPE,
	TRUNC,
	INPUT,
	APPEND,
	HEREDOC,
	LIMITER,
	FD,
}					t_type;

typedef enum e_error
{
	Q_ERROR = -1,
	PIPE_ERROR = -2,
	MISSING_FILENAME = -3,
	INVALID_OPERATOR = -4,
}					t_error;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
	struct s_env	*previous;
}					t_env;

typedef struct s_tool
{
	char			pwd[PATH_MAX];
	char			old_pwd[PATH_MAX];
}					t_tool;

typedef struct s_lexer
{
	char			*str;
	int				i;
	struct s_lexer	*next;
}					t_lexer;

typedef struct s_cmd
{
	char			**argv;
	char			*infile;
	char			*outfile;
	bool			append;
	bool			heredoc;
	t_lexer			*lexer;
	struct s_cmd	*next;
	struct s_cmd	*previous;
}					t_cmd;

typedef struct s_obj
{
	t_token			*token;
	t_cmd			*cmd;
	t_env			*env;
	t_tool			*tool;
	char			*input;
	int				*pid;
	int				exit_code;
}					t_obj;

typedef struct s_builtin
{
	char			*str;
	int				(*function)(char **argv, t_obj *obj);
}					t_buildin;

/* ********* srcs ************* */
int		main(int argc, char *argv[], char **envp);

/* ********* parsing ********** */
void	parsing(t_obj *obj);
void	quote_error(char *str);
int		check_quotes(char *str);
t_token	*tokenize(char *str);
int		check_syntax(t_token *head);

/* ***** cleanup function ***** */
void	free_token(t_token *token);

/* ***** linked list functions ***** */
t_cmd	*append_cmd(t_cmd *head, t_cmd *node);
t_token	*append_token(t_token *head, t_token *node);

/* ******* display functions ******* */
void	print_cmd(t_cmd *cmd);
void	print_list(t_token *list);

#endif
