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
#include "after_fork.h"
#include <unistd.h>

static char	*find_bin_from_path(char *bin, char **paths)
{
	char	**path_tried;
	char	*full_path;

	path_tried = paths;
	while (*path_tried)
	{
		full_path = ft_strjoin(*path_tried, bin);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		path_tried++;
	}
	return (NULL);
}

static char	*make_full_path(char *bin, char **paths)
{
	if (ft_strchr(bin, '/') == NULL)
		return (find_bin_from_path(bin, paths));
	if (access(bin, X_OK) == 0)
		return (ft_strdup(bin));
	return (NULL);
}

int	parse_args(t_execinfo *e, t_procinfo *p, int at)
{
	char	**args_split;

	args_split = ft_split_escape(p->coms[at], ' ');
	if (!args_split)
		return (1);
	e->bin = make_full_path(args_split[0], p->paths);
	if (!e->bin)
	{
		ft_dprintf(2, "pipex: %s: command not found\n", args_split[0]);
		strarr2_del(args_split);
		return (127);
	}
	e->args = strarr2_dup(args_split, 0, strarr2len(args_split));
	if (!e->args)
		return (1);
	free(e->args[0]);
	strarr2_del(args_split);
	args_split = ft_split(e->bin, '/');
	if (!args_split)
		return (1);
	e->args[0] = ft_strdup(args_split[strarr2len(args_split) - 1]);
	if (!e->args[0])
		return (1);
	return (0);
}