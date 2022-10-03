/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:32:56 by donghyle          #+#    #+#             */
/*   Updated: 2022/10/03 17:32:57 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "datatypes.h"
# define IN 0
# define OUT 1

int	fork_ntimes(t_execinfo *e, int n);
int	set_stdin_stdout(t_execinfo *e, int n);
#endif
