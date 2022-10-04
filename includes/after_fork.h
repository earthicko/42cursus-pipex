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

int	fork_ntimes(t_procinfo *e, int n);
int	set_stdin_stdout(t_procinfo *e, int n);
int	parse_args(t_execinfo *e, t_procinfo *p, int at);

char	**ft_split_escape(char const *s, char c);
#endif
