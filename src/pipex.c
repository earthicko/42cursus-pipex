#include "parser.h"
#include "forker.h"
#include "libft.h"

int main(int argc, char **argv, char **envp)
{
	t_execinfo	*execinfo;

	execinfo = construct_execinfo(argc, argv, envp);
	if (!execinfo)
		return (1);
	// ft_printf("return :%d\n", fork_ntimes(execinfo, execinfo->n_command));
	execinfo_del(execinfo);
	return (0);
}
