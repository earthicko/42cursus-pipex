#include "pipex.h"
#include "parser.h"
#include "utils.h"
#include <unistd.h>
#include <fcntl.h>

int	is_access_denied(char *infile, char *outfile)
{
	if (access(infile, R_OK))
	{
		ft_printf("infile access denied\n");
		return (1);
	}
	if (access(outfile, W_OK))
	{
		ft_printf("outfile access denied\n");
		return (1);
	}
	return (0);
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

t_execinfo	*execinfo_del(t_execinfo *execinfo)
{
	// fd_pipe 닫기 추가
	if (execinfo->bins)
		free_strs(execinfo->bins);
	// if (execinfo->envp)
	// 	free_strs(execinfo->envp);
	free(execinfo);
	return (NULL);
}

static int	open_in_out_files(t_execinfo *execinfo, int argc, char **argv)
{
	if (is_access_denied(argv[1], argv[argc - 1]))
		return (-1);
	execinfo->fd_in = open(argv[1], O_RDONLY);
	if (execinfo->fd_in < 0)
		return (-1);
	execinfo->fd_out = open(argv[argc - 1], O_WRONLY);
	if (execinfo->fd_out < 0)
	{
		close(execinfo->fd_in);
		return (-1);
	}
	return (0);
}

static int	deploy_pipes(int **pipes, int n_pipes)
{
	int	i;
	
	i = 0;
	while (i < n_pipes)
	{
		if (pipe(pipes[i]))
		{
			revert_deploy_pipes(pipes, i - 1);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	create_pipes(t_execinfo *execinfo)
{
	int	n_pipes;
	int	i;

	n_pipes = execinfo->n_command - 1;
	execinfo->fd_pipes = intarrs_init(n_pipes, 2);
	if (!execinfo->fd_pipes)
		return (-1);
	if (deploy_pipes(execinfo->fd_pipes, n_pipes)
	{
		free_intarrs(execinfo->fd_pipes);
		return (-1);
	}
	return (0);
}

t_execinfo	*construct_execinfo(int argc, char **argv, char **envp)
{
	t_execinfo	*execinfo;
	char	**paths;

	execinfo = execinfo_init();
	if (!execinfo)
		return (NULL);
	if (argc - 3 < 2)
		return (NULL);
	execinfo->n_command = argc - 3;
	if (open_in_out_files(execinfo, argc, argv))
		return (execinfo_del(execinfo));
	paths = parse_paths(envp);
	if (!paths)
		return (execinfo_del(execinfo));
	execinfo->bins = make_full_bin_paths(argc, argv, paths);
	if (!execinfo->bins)
		return (execinfo_del(execinfo));
	if (create_pipes(execinfo))
		return (execinfo_del(execinfo));
	return (execinfo);
}
