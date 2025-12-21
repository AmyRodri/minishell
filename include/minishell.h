/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:23:31 by kamys             #+#    #+#             */
/*   Updated: 2026/01/13 15:59:43 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "env.h"
# include "built.h"
# include "lexer.h"
# include "utils.h"
# include "parser.h"
# include "exec.h"
# include "colors.h"
# include "prompt.h"

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

// signal.c
int				get_singal(void);
void			reset_signal(void);
void			handler(int sig);
void			setup_sig(void);



#endif
