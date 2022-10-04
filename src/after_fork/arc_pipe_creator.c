/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_creator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:33:55 by donghyle          #+#    #+#             */
/*   Updated: 2022/10/03 17:33:56 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datatypes.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	open_in_out_files(t_procinfo *procinfo, int argc, char **argv)
{
	procinfo->fd_in = open(argv[1], O_RDONLY);
	if (procinfo->fd_in < 0)
	{
		perror(NULL);
		return (-1);
	}
	procinfo->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (procinfo->fd_out < 0)
	{
		perror(NULL);
		if (close(procinfo->fd_in))
			perror(NULL);
		return (-1);
	}
	return (0);
}
