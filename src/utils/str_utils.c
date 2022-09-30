#include "libft.h"

int	**intarrs_init(int n, int m)
{
	int	**intarrs;
	int	i;

	intarrs = (int **)malloc(sizeof(int *) * (n + 1));
	if (!intarrs)
		return (-1);
	ft_memset(intarrs, 0, sizeof(int *) * (n + 1));
	i = 0;
	while (i < n)
	{
		intarrs[i] = (int *)malloc(sizeof(int) * m);
		if (!intarrs[i])
		{
			free_intarrs(intarrs);
			return (NULL);
		}
		i++;
	}
	return (intarrs);
}

void	free_intarrs(int **arrs)
{
	int	**cursor;

	cursor = arrs;
	if (!cursor)
		return ;
	while (*cursor)
	{
		free(*cursor);
		cursor++;
	}
	free(arrs);
}

void	free_strs(char **strs)
{
	char	**cursor;

	cursor = strs;
	if (!cursor)
		return ;
	while (*cursor)
	{
		free(*cursor);
		cursor++;
	}
	free(strs);
}

int	append_slash(char **paths)
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
