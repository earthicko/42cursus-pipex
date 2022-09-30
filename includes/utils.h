#ifndef UTILS_H
# define UTILS_H

int		**intarrs_init(int n, int m);
void	free_intarrs(int **arrs);
void	free_strs(char **strs);
int		append_slash(char **paths);
#endif
