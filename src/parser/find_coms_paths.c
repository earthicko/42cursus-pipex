/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_coms_paths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:33:53 by donghyle          #+#    #+#             */
/*   Updated: 2022/10/03 17:33:54 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "before_fork.h"
#include <unistd.h>

static int	append_slash(char **paths)
{
	char	**cursor;
	char	*appended;

	cursor = paths;
	while (*cursor)
	{
		appended = ft_strjoin(*cursor, "/");
		if (!appended)
			return (-1);
		free(*cursor);
		*cursor = appended;
		cursor++;
	}
	return (0);
}

static char	*find_path_var_pointer(char **envp)
{
	char	**cursor;

	cursor = envp;
	while (*cursor)
	{
		if (ft_strncmp(*cursor, "PATH=", 5) == 0)
			break ;
		cursor++;
	}
	return (*cursor);
}

static char	**parse_paths(char **envp)
{
	char	*path_var;
	char	**paths;

	path_var = find_path_var_pointer(envp);
	if (!path_var)
		return (NULL);
	path_var = ft_substr(path_var, 5, ft_strlen(path_var));
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	free(path_var);
	if (!paths)
		return (NULL);
	if (append_slash(paths))
	{
		strarr2_del(paths);
		return (NULL);
	}
	return (paths);
}

int	find_coms_paths(t_procinfo *e, int argc, char **argv, char **envp)
{
	int		i;

	e->paths = parse_paths(envp);
	if (!e->paths)
		return (-1);
	e->coms = (char **)malloc(sizeof(char *) * (argc - 2));
	if (!e->coms)
		return (-1);
	ft_memset(e->coms, 0, sizeof(char *) * (argc - 2));
	i = 2;
	while (i < argc - 1)
	{
		e->coms[i - 2] = ft_strdup(argv[i]);
		if (!e->coms[i - 2])
			return (-1);
		i++;
	}
	e->coms[i - 2] = NULL;
	return (0);
}
