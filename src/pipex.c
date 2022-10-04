/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:33:13 by donghyle          #+#    #+#             */
/*   Updated: 2022/10/03 17:33:17 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "before_fork.h"
#include "after_fork.h"
#include <stdio.h>

#include <unistd.h>
#include "libft.h"

int	main(int argc, char **argv, char **envp)
{
	t_procinfo	*procinfo;
	int			error;

	procinfo = construct_procinfo(argc, argv, envp);
	if (!procinfo)
		return (1);
	error = fork_ntimes(procinfo, procinfo->n_proc);
	if (error)
		perror(NULL);
	procinfo_del(procinfo);
	ft_printf("%d: return %d\n", getpid(), error);
	return (error);
}
