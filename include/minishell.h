/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:43:33 by mberthou          #+#    #+#             */
/*   Updated: 2025/06/09 17:15:48 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_token
{
	char			*name;
	int				type;
	struct s_token	*next;
	struct s_token	*previous;
}					t_token;

typedef enum e_type
{
	EMPTY,
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
	/* INVALID_OPERATOR_<< = -5, */
	/* INVALID_OPERATOR_> = -6, */
	/* INVALID_OPERATOR_>> = -7, */
}					t_error;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
	struct s_env	*previous;
}					t_env;

typedef struct s_tool
{
	char			*pwd;
	char			*old_pwd;
}					t_tool;

typedef struct	s_redirections
{
	char			*name;
	int				type;
	struct s_lexer	*next;
}					t_redirections;

typedef struct s_cmd
{
	char			**argv;
	char			*infile;
	char			*outfile;
	int				append;
	int				heredoc;
	t_redirections	*redirections;
	struct s_cmd	*next;
	struct s_cmd	*previous;
}					t_cmd;

typedef struct s_obj
{
	t_token			*token;
	t_cmd			*cmd;
	t_env			*env;
	t_tool			*tool;
	char			*str;
	int				*pid;
	int				exit_code;
}					t_obj;

typedef struct s_buildin
{
	char			*str;
	int				(*function)(char **argv, t_obj *obj);
}					t_buildin;

/* ********* srcs ************* */
int					main(int argc, char *argv[], char **envp);

/* ********* parsing ********** */
void				quote_error(char *str);
int					check_quotes(char *str);
t_token				*tokenize(char *str);
int					check_syntax(t_token *head);
void				print_list(t_token *list);

/* ********* parsing ********** */
char				*expand_var(char *str, char **envp);
int					is_expand(char *str);
char				*after_dollar(char *str, int *i, char **envp);
char				*get_value(char *var_name, char **envp);
int					check_char(char c);
char				*special_case(char *str, int *i);
char				*join_and_free(char *s1, char *s2);
char				*expand_it(char *str, char **envp);
char				*get_varname(char *str, int *i, int start);

/* ***** cleanup function ***** */
void				free_list(t_token *token);

#endif
