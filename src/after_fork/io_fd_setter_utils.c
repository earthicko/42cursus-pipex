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

#include "libft.h"
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

int	heredoc_end(char *limiter, char *line)
{
	size_t	len_limiter;

	len_limiter = ft_strlen(limiter);
	if (len_limiter != ft_strlen(line) - 1)
		return (0);
	if (ft_strncmp(limiter, line, len_limiter))
		return (0);
	if (line[len_limiter] != '\n')
		return (0);
	return (1);
}
