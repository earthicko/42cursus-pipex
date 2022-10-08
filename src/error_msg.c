/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:32:56 by donghyle          #+#    #+#             */
/*   Updated: 2022/10/03 17:32:57 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error_msg.h"
#include <stdio.h>
#include <unistd.h>

void	perror_and_exit(char *prefix, int stat)
{
	perror(prefix);
	exit(stat);
}

void	perror_nofile_and_exit(char *filename, int stat)
{
	ft_dprintf(STDERR_FILENO, "%s: ", SHELL_NAME);
	ft_dprintf(STDERR_FILENO, "%s: No such file or directory\n", filename);
	exit(stat);
}

void	perror_permission_denied_and_exit(char *filename, int stat)
{
	ft_dprintf(STDERR_FILENO, "%s: ", SHELL_NAME);
	ft_dprintf(STDERR_FILENO, "%s: Permission denied\n", filename);
	exit(stat);
}

void	perror_command_not_found_and_exit(char *filename, int stat)
{
	ft_dprintf(STDERR_FILENO, "%s: ", SHELL_NAME);
	ft_dprintf(STDERR_FILENO, "%s: command not found\n", filename);
	exit(stat);
}
