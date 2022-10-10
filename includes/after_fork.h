/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_fork.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:32:56 by donghyle          #+#    #+#             */
/*   Updated: 2022/10/03 17:32:57 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFTER_FORK_H
# define AFTER_FORK_H
# include "datatypes.h"
# define IN 0
# define OUT 1

int		fork_ntimes(t_procinfo *e, int n);
void	close_all_pipes(t_procinfo *p);
int		heredoc_end(char *limiter, char *line);
void	set_stdin_stdout(t_procinfo *e, int n);
char	*make_full_path(char *bin, char **paths);
void	parse_args(t_execinfo *e, t_procinfo *p, int at);
#endif
