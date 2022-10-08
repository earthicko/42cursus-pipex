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
	perror_command_not_found_and_exit(bin, 127);
	return (NULL);
}

static char	*find_bin_from_same_dir(char *bin)
{
	char	*in_same_dir;

	in_same_dir = ft_substr(bin, 2, ft_strlen(bin) - 2);
	// ft_dprintf(2, "%d: find_bin_from_same_dir: %s\n", getpid(), in_same_dir);
	strip_quotes(&in_same_dir);
	// ft_dprintf(2, "%d: find_bin_from_same_dir: %s\n", getpid(), in_same_dir);
	escape_quotes(&in_same_dir);
	// ft_dprintf(2, "%d: find_bin_from_same_dir: %s\n", getpid(), in_same_dir);
	if (!in_same_dir)
		return (NULL);
	if (access(in_same_dir, F_OK))
		perror_nofile_and_exit(bin, 127);
	if (access(in_same_dir, X_OK))
		perror_permission_denied_and_exit(bin, 126);
	return (in_same_dir);
}

static char	*find_bin_from_root(char *bin)
{
	// ft_dprintf(2, "%d: find_bin_from_root\n", getpid());
	if (access(bin, F_OK))
		perror_nofile_and_exit(bin, 127);
	if (access(bin, X_OK))
		perror_permission_denied_and_exit(bin, 126);
	// ft_dprintf(2, "%d: found from %s\n", getpid(), bin);
	return (ft_strdup(bin));
}

static char	*make_full_path(char *bin, char **paths)
{
	if (ft_strncmp(bin, "./", 2) == 0)
		return (find_bin_from_same_dir(bin));
	if (ft_strchr(bin, '/') == NULL)
		return (find_bin_from_path(bin, paths));
	return (find_bin_from_root(bin));
}

char	**postprocess_args(char **args_split, char *bin)
{
	char	**bin_dirs;
	char	**processed;
	char	**cursor;

	processed = strarr2_dup(args_split, 0, strarr2len(args_split));
	if (!processed)
		return (NULL);
	free(processed[0]);
	bin_dirs = ft_split(bin, '/');
	if (!bin_dirs)
	{
		strarr2_del(processed);
		return (NULL);
	}
	processed[0] = ft_strdup(bin_dirs[strarr2len(bin_dirs) - 1]);
	strarr2_del(bin_dirs);
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

	// ft_dprintf(2, "%d: before args_split: %s\n", getpid(), p->coms[at]);
	args_split = ft_split_args(p->coms[at]);
	if (!args_split)
		exit(1);
	// ft_dprintf(2, "%d: args_split: \n", getpid());
	// char **str = args_split;while(*str){ft_dprintf(2, "%d: [%s]\n", getpid(), *str);str++;}
	e->bin = make_full_path(args_split[0], p->paths);
	if (!e->bin)
		exit(1);
	e->args = postprocess_args(args_split, e->bin);
	free(args_split);
	// ft_dprintf(2, "%d: processed: \n", getpid());
	// char **str2 = e->args;while(*str2){ft_dprintf(2, "%d: [%s]\n", getpid(), *str2);str2++;}
	if (!e->args)
		exit(1);
}
