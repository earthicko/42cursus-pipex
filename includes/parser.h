/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:32:57 by donghyle          #+#    #+#             */
/*   Updated: 2022/10/03 17:32:59 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "datatypes.h"

t_execinfo	*construct_execinfo(int argc, char **argv, char **envp);

int			find_bin_paths(t_execinfo *e, int argc, char **argv, char **paths);
int			parse_args(t_execinfo *e, int at, char *args, char **paths);
int			open_in_out_files(t_execinfo *e, int argc, char **argv);
int			create_pipes(t_execinfo *e);
#endif
