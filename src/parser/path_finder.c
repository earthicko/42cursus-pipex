#include "libft.h"
#include "datatypes.h"
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

static char	**parse_paths(char **envp)
{
	char	**cursor;
	char	*paths_condensed;
	char	**paths;

	cursor = envp;
	while (*cursor)
	{
		if (ft_strncmp(*cursor, "PATH=", ft_strlen("PATH=")) == 0)
			break ;
		cursor++;
	}
	if (!(*cursor))
		return (NULL);
	paths_condensed = ft_substr(*cursor, ft_strlen("PATH="), ft_strlen(*cursor));
	if (!paths_condensed)
		return (NULL);
	paths = ft_split(paths_condensed, ':');
	free(paths_condensed);
	if (!paths)
		return (NULL);
	if (append_slash(paths))
	{
		strarr2_del(paths);
		return (NULL);
	}
	return (paths);
}

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

static int	parse_args(t_execinfo *e, int at, char *args, char **paths)
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
	e->args[at] = strarr2_dup(args_split, 1, strarr2len(args_split));
	if (!e->args[at])
	{
		free(e->bins[at]);
		return (-1);
	}
	strarr2_del(args_split);
	return (0);
}

int	find_bin_paths(t_execinfo *e, int argc, char **argv, char **envp)
{
	int		i;
	char	**paths;

	paths = parse_paths(envp);
	if (!paths)
		return (-1);
	e->bins = (char **)malloc(sizeof(char *) * (argc - 2));
	if (!e->bins)
	{
		strarr2_del(paths);
		return (-1);
	}
	ft_memset(e->bins, 0, sizeof(e->bins));
	e->args = (char ***)malloc(sizeof(char **) * (argc - 2));
	if (!e->args)
	{
		strarr2_del(paths);
		return (-1);
	}
	i = 2;
	while (i < argc - 1)
	{
		if (parse_args(e, i - 2, argv[i], paths))
		{
			strarr2_del(paths);
			strarr2_del(e->bins);
			e->bins = NULL;
			return (-1);
		}
		i++;
	}
	e->bins[i - 2] = NULL;
	strarr2_del(paths);
	return (0);
}
