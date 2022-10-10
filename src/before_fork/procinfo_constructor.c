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

#include "libft.h"
#include "before_fork.h"
#include "parser.h"
#include <stddef.h>

t_procinfo	*construct_procinfo_heredoc(int argc, char **argv, char **envp)
{
	t_procinfo	*procinfo;

	procinfo = procinfo_init();
	if (!procinfo)
		return (NULL);
	procinfo->n_proc = argc - 4;
	procinfo->limiter = ft_strdup(argv[2]);
	if (!procinfo->limiter)
		return (procinfo_del(procinfo));
	procinfo->infile = HEREDOC_FILENAME;
	procinfo->outfile = argv[argc - 1];
	if (split_command_heredoc(procinfo, argc, argv, envp))
		return (procinfo_del(procinfo));
	if (create_pipes(procinfo))
		return (procinfo_del(procinfo));
	procinfo->envp = envp;
	return (procinfo);
}

t_procinfo	*construct_procinfo(int argc, char **argv, char **envp)
{
	t_procinfo	*procinfo;

	if (argc - 3 < 2)
		return (NULL);
	if (!ft_strncmp(argv[1], "here_doc", 9))
		return (construct_procinfo_heredoc(argc, argv, envp));
	procinfo = procinfo_init();
	if (!procinfo)
		return (NULL);
	procinfo->n_proc = argc - 3;
	procinfo->infile = argv[1];
	procinfo->outfile = argv[argc - 1];
	if (split_command(procinfo, argc, argv, envp))
		return (procinfo_del(procinfo));
	if (create_pipes(procinfo))
		return (procinfo_del(procinfo));
	procinfo->envp = envp;
	return (procinfo);
}
