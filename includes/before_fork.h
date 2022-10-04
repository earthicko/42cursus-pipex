/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_fork.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:32:57 by donghyle          #+#    #+#             */
/*   Updated: 2022/10/03 17:32:59 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BEFORE_FORK_H
# define BEFORE_FORK_H
# include "datatypes.h"

t_procinfo	*construct_procinfo(int argc, char **argv, char **envp);

int			find_coms_paths(t_procinfo *e, int argc, char **argv, char **paths);
int			create_pipes(t_procinfo *e);
#endif
