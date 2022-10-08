/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:33:50 by donghyle          #+#    #+#             */
/*   Updated: 2022/10/03 17:33:51 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error_msg.h"
#include "parser.h"
#include "after_fork.h"
#include <unistd.h>

static void	put_bin_name_on_args(char **args, char *bin_path)
{
	char	**bin_dirs;

	free(args[0]);
	bin_dirs = ft_split(bin_path, '/');
	if (!bin_dirs)
	{
		args[0] = NULL;
		return ;
	}
	args[0] = ft_strdup(bin_dirs[strarr2len(bin_dirs) - 1]);
	strarr2_del(bin_dirs);
}

char	**postprocess_args(char **args_split, char *bin_path)
{
	char	**processed;
	char	**cursor;

	processed = strarr2_dup(args_split, 0, strarr2len(args_split));
	if (!processed)
		return (NULL);
	put_bin_name_on_args(processed, bin_path);
	if (!processed[0])
	{
		strarr2_del(processed);
		return (NULL);
	}
	cursor = processed;
	while (*cursor)
	{
		escape_quotes(cursor);
		cursor++;
	}
	return (processed);
}

void	parse_args(t_execinfo *e, t_procinfo *p, int at)
{
	char	**args_split;

	args_split = ft_split_args(p->coms[at]);
	if (!args_split)
		exit(1);
	e->bin = make_full_path(args_split[0], p->paths);
	if (!e->bin)
		exit(1);
	e->args = postprocess_args(args_split, e->bin);
	free(args_split);
	if (!e->args)
		exit(1);
}
