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

void	skip_space(char **str, int inverted);
char	**ft_split_args(char const *s);
int		split_command(t_procinfo *e, int c, char **v, char **envp);
int		split_command_heredoc(t_procinfo *e, int c, char **v, char **envp);
int		ft_isquote(int c);
int		ft_isquote_literal(char *p_c);
int		ft_isquote_escape(char *p_c);
void	strip_quotes(char **p_str);
void	escape_quotes(char **p_str);
#endif
