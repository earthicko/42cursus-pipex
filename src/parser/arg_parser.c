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
#include "datatypes.h"
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

static int	abort_parse_args(t_execinfo *e, int at)
{
	if (e->bins[at])
		free(e->bins[at]);
	if (e->args[at])
		strarr2_del(e->args[at]);
	return (-1);
}

int	parse_args(t_execinfo *e, int at, char *args, char **paths)
{
	char	**args_split;

	args_split = ft_split(args, ' ');
	if (!args_split)
		return (-1);
	e->bins[at] = make_full_path(args_split[0], paths);
	if (!e->bins[at])
	{
		ft_printf("pipex: command not found: %s\n", args_split[0]);
		return (-1);
	}
	e->args[at] = strarr2_dup(args_split, 0, strarr2len(args_split));
	if (!e->args[at])
		return (abort_parse_args(e, at));
	free(e->args[at][0]);
	strarr2_del(args_split);
	args_split = ft_split(e->bins[at], '/');
	if (!args_split)
		return (abort_parse_args(e, at));
	e->args[at][0] = ft_strdup(args_split[strarr2len(args_split) - 1]);
	if (!e->args[at][0])
		return (abort_parse_args(e, at));
	return (0);
}
