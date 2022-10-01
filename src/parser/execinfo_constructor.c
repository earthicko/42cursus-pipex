#include "parser.h"
#include <stddef.h>
#include "libft.h"

t_execinfo	*construct_execinfo(int argc, char **argv, char **envp)
{
	t_execinfo	*execinfo;

	execinfo = execinfo_init();
	if (!execinfo)
		return (NULL);
	if (argc - 3 < 2)
		return (NULL);
	execinfo->n_command = argc - 3;
	if (find_bin_paths(execinfo, argc, argv, envp))
		return (execinfo_del(execinfo));
	if (open_in_out_files(execinfo, argc, argv))
		return (execinfo_del(execinfo));
	if (create_pipes(execinfo))
		return (execinfo_del(execinfo));
	execinfo->envp = envp;
	return (execinfo);
}
