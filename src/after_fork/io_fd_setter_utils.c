/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_fd_setter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:34:08 by donghyle          #+#    #+#             */
/*   Updated: 2022/10/03 17:34:11 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "after_fork.h"
#include <unistd.h>

void	close_all_pipes(t_procinfo *p)
{
	int	i;

	i = 0;
	while (i < p->n_proc - 1)
	{
		close(p->fd_pipes[i][IN]);
		close(p->fd_pipes[i][OUT]);
		i++;
	}
}
