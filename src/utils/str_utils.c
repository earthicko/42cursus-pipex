#include "libft.h"

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
