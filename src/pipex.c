#include "parser.h"
#include "utils.h"
#include <unistd.h>

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

int main(int argc, char **argv, char **envp)
{
	char	**bins;
	char	**paths;

	if (argc - 3 < 2) return 1;
	if (is_access_denied(argv[1], argv[argc - 1]))
		return (1);
	paths = parse_paths(envp);
	if (!paths)
		return (1);
	bins = make_full_bin_paths(argc, argv, paths);
	if (!bins)
	{
		free_strs(paths);
		return (1);
	}
	return 0;
}
