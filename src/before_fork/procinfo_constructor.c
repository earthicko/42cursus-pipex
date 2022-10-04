/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procinfo_constructor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:33:51 by donghyle          #+#    #+#             */
/*   Updated: 2022/10/03 17:33:52 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "before_fork.h"
#include "parser.h"
#include <stddef.h>

t_procinfo	*construct_procinfo(int argc, char **argv, char **envp)
{
	t_procinfo	*procinfo;

	if (argc - 3 < 2)
		return (NULL);
	procinfo = procinfo_init();
	if (!procinfo)
		return (NULL);
	procinfo->n_proc = argc - 3;
	procinfo->infile = argv[1];
	procinfo->outfile = argv[argc - 1];
	if (find_coms_paths(procinfo, argc, argv, envp))
		return (procinfo_del(procinfo));
	if (create_pipes(procinfo))
		return (procinfo_del(procinfo));
	procinfo->envp = envp;
	return (procinfo);
}
