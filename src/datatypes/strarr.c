#include "libft.h"
#include "datatypes.h"

int	strarr2len(char **arr)
{
	int	len;

	len = 0;
	while (*arr)
	{
		len++;
		arr++;
	}
	return (len);
}

char	**strarr2_dup(char **arr, int from, int to)
{
	char	**dup;
	int		i;

	if (!arr || to - from < 0)
		return (NULL);
	dup = (char **)malloc(sizeof(char *) * (to - from + 1));
	if (!dup)
		return (NULL);
	ft_memset(dup, 0, sizeof(char *) * (to - from + 1));
	i = 0;
	while (i < to - from)
	{
		dup[i] = ft_strdup(arr[i + from]);
		if (!dup[i])
		{
			strarr2_del(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	strarr2_del(char **arr)
{
	char	**cursor;

	if (!arr)
		return ;
	cursor = arr;
	while (*cursor)
	{
		free(*cursor);
		cursor++;
	}
	free(arr);
}

void	strarr3_del(char ***arr)
{
	char	***cursor;

	if (!arr)
		return ;
	cursor = arr;
	while (*cursor)
	{
		strarr2_del(*cursor);
		cursor++;
	}
	free(arr);
}
