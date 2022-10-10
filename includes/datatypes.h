/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datatypes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:32:51 by donghyle          #+#    #+#             */
/*   Updated: 2022/10/03 17:32:54 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATATYPES_H
# define DATATYPES_H
# define HEREDOC_FILENAME ".heredoc_tmp"

typedef struct s_procinfo
{
	int		n_proc;
	int		**fd_pipes;
	char	*infile;
	char	*outfile;
	char	*limiter;
	char	**coms;
	char	**paths;
	char	**envp;
}	t_procinfo;

typedef struct s_execinfo
{
	char	*bin;
	char	**args;
}	t_execinfo;

t_procinfo	*procinfo_init(void);
t_procinfo	*procinfo_del(t_procinfo *procinfo);

t_execinfo	*execinfo_init(void);
t_execinfo	*execinfo_del(t_execinfo *execinfo);

int			**intarr2_init(int n, int m);
void		intarr2_del(int **arrs);

char		**strarr2_dup(char **arr, int from, int to);
int			strarr2len(char **arr);
void		strarr2_del(char **strs);

void		strarr3_del(char ***arr);
#endif
