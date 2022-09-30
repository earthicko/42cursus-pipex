#ifndef PARSER_H
# define PARSER_H
# include "libft.h"

char	**parse_paths(char **envp);
char	**make_full_bin_paths(int argc, char **argv, char **paths);
#endif
