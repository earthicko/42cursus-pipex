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

#ifndef ERROR_MSG_H
# define ERROR_MSG_H
# define SHELL_NAME "pipex"

void	perror_and_exit(char *prefix, int stat);
void	perror_nofile_and_exit(char *filename, int stat);
void	perror_permission_denied_and_exit(char *filename, int stat);
void	perror_command_not_found_and_exit(char *filename, int stat);
#endif
