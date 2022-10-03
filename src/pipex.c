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

#include "parser.h"
#include "executor.h"
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	t_execinfo	*execinfo;
	int			error;

	execinfo = construct_execinfo(argc, argv, envp);
	if (!execinfo)
		return (1);
	error = fork_ntimes(execinfo, execinfo->n_proc);
	if (error)
		perror(NULL);
	execinfo_del(execinfo);
	return (0);
}
