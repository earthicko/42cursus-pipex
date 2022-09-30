#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_execinfo
{
	int		n_command;
	int		fd_in;
	int		fd_out;
	int		**fd_pipes;
	char	**bins;
	char	**envp;
}	t_execinfo;

t_execinfo	*construct_execinfo(int argc, char **argv, char **envp);
#endif
