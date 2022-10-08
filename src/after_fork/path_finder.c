/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
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
	strip_quotes(&in_same_dir);
	escape_quotes(&in_same_dir);
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
	if (access(bin, F_OK))
		perror_nofile_and_exit(bin, 127);
	if (access(bin, X_OK))
		perror_permission_denied_and_exit(bin, 126);
	return (ft_strdup(bin));
}

char	*make_full_path(char *bin, char **paths)
{
	if (ft_strncmp(bin, "./", 2) == 0)
		return (find_bin_from_same_dir(bin));
	if (ft_strchr(bin, '/') == NULL)
		return (find_bin_from_path(bin, paths));
	return (find_bin_from_root(bin));
}
