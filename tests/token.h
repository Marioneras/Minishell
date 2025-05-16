/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:43:33 by mberthou          #+#    #+#             */
/*   Updated: 2025/05/16 17:15:26 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
#define	MINISHELL_H 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "libftprintf.h"


typedef struct	s_token
{
	char			*name;
	int				type;
	struct s_token	*next;
}	t_token;

typedef enum	s_type
{
	CMD,
	BUILD_IN,
	ARGUMENT,
	PIPE,
	REDIRECTION,
	FD,
} t_type;

typedef struct	s_env
{
	char			*value;
	struct s_env	*next;
	struct s_env	*previous;
}	t_env;

typedef struct	s_tool
{
	char	*pwd;
	char	*old_pwd;
}	t_tool;

typedef struct	s_lexer
{
	char			*str;
	int				i;
	struct s_lexer	*next;
}	t_lexer;

typedef struct	s_cmd
{
	char			**argv;
	char			*infile;
	char			*outfile;
	int				append;
	int				heredoc;
	t_lexer			*lexer;
	struct s_cmd	*next;
	struct s_cmd	*previous;
}	t_cmd;

typedef struct	s_obj
{
	t_token	*token;
	t_cmd	*cmd;
	t_env	*env;
	t_tool	*tool;
	char	*str;
	int		*pid;
	int		exit_code;
}	t_obj;

typedef struct	s_buildin
{
	char	*str;
	int		(*function)(char **argv, t_obj *obj);
}	t_buildin;

#endif
