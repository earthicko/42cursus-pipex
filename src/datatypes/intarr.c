#include "libft.h"

void	intarr2_del(int **arrs)
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

int	**intarr2_init(int n, int m)
{
	int	**intarrs;
	int	i;

	intarrs = (int **)malloc(sizeof(int *) * (n + 1));
	if (!intarrs)
		return (NULL);
	ft_memset(intarrs, 0, sizeof(int *) * (n + 1));
	i = 0;
	while (i < n)
	{
		intarrs[i] = (int *)malloc(sizeof(int) * m);
		if (!intarrs[i])
		{
			intarr2_del(intarrs);
			return (NULL);
		}
		i++;
	}
	return (intarrs);
}
