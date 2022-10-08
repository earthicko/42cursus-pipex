/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:32:56 by donghyle          #+#    #+#             */
/*   Updated: 2022/10/03 17:32:57 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "datatypes.h"

char	**ft_split_args(char const *s);
int		find_coms_paths(t_procinfo *e, int argc, char **argv, char **paths);
int		ft_isquote(int c);
int		ft_isquote_literal(char *p_c);
int		ft_isquote_escape(char *p_c);
void	strip_quotes(char **p_str);
void	escape_quotes(char **p_str);
#endif
