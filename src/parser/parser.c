#include "libft.h"
#include "utils.h"
#include "pipex.h"
#include <unistd.h>

char	**parse_paths(char **envp)
{
	char	**cursor;
	char	*paths_condensed;
	char	**paths;
	int		error;

	cursor = envp;
	while (*cursor)
	{
		if (ft_strncmp(*cursor, "PATH=", ft_strlen("PATH=")) == 0)
			break ;
		cursor++;
	}
	paths_condensed = ft_substr(*cursor, ft_strlen("PATH="), ft_strlen(*cursor));
	if (!paths_condensed)
		return (NULL);
	paths = ft_split(paths_condensed, ':');
	free(paths_condensed);
	if (!paths)
		return (NULL);
	error = append_slash(paths);
	if (error)
	{
		free_strs(paths);
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
		return (bin);
	return (NULL);
}

char	**make_full_bin_paths(int argc, char **argv, char **paths)
{
	char	**bins;
	int		i_arg;
	int		i_bin;

	bins = (char **)malloc(sizeof(char *) * (argc - 3));
	ft_memset(bins, 0, sizeof(bins));
	i_arg = 2;
	i_bin = 0;
	while (i_arg < argc - 1)
	{
		bins[i_bin] = make_full_path(argv[i_arg], paths);
		if (!bins[i_bin])
		{
			free_strs(bins);
			return (NULL);
		}
		i_arg++;
		i_bin++;
	}
	bins[i_bin] = NULL;
	return (bins);
}

t_execinfo	*execinfo_init(void)
{
	t_execinfo	*init;

	init = (t_execinfo *)malloc(sizeof(t_execinfo));
	if (!init)
		return (NULL);
	ft_memset(init, 0, sizeof(t_execinfo));
	return (init);
}

t_execinfo	*construct_execinfo(int argc, char **argv, char **envp)
{
	t_execinfo	*execinfo;
	char	**paths;

	execinfo = execinfo_init();
	if (!execinfo)
		return (NULL);
	if (argc - 3 < 2 || is_access_denied(argv[1], argv[argc - 1]))
		return (NULL);
	paths = parse_paths(envp);
	if (!paths)
		return (NULL);
	execinfo->bins = make_full_bin_paths(argc, argv, paths);
	if (!execinfo->bins)
	{
		free_strs(paths);
		return (NULL);
	}
}
