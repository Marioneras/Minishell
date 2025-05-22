/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:43:33 by mberthou          #+#    #+#             */
/*   Updated: 2025/05/20 19:53:04 by mberthou         ###   ########.fr       */
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
	INVALID_OPERATOR_< = -4,
	INVALID_OPERATOR_<< = -5,
	INVALID_OPERATOR_> = -6,
	INVALID_OPERATOR_>> = -7,
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
	int				append;
	int				heredoc;
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
	char			*str;
	int				*pid;
	int				exit_code;
}					t_obj;

typedef struct s_buildin
{
	char			*str;
	int				(*function)(char **argv, t_obj *obj);
}					t_buildin;

/* ********* parsing ********** */
int	check_syntax(t_token *head);

#endif
