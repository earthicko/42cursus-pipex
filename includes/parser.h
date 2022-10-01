#ifndef PARSER_H
# define PARSER_H
# include "datatypes.h"

t_execinfo	*construct_execinfo(int argc, char **argv, char **envp);

int			find_bin_paths(t_execinfo *e, int argc, char **argv, char **paths);
int			open_in_out_files(t_execinfo *e, int argc, char **argv);
int			create_pipes(t_execinfo *e);
#endif
