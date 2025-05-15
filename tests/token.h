/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:43:33 by mberthou          #+#    #+#             */
/*   Updated: 2025/05/13 11:17:15 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	TOKEN_H
#define TOKEN_H

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

#endif
