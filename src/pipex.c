#include "parser.h"
#include "forker.h"

int main(int argc, char **argv, char **envp)
{
	t_execinfo	*execinfo;

	execinfo = construct_execinfo(argc, argv, envp);
	if (!execinfo)
		return (1);
	fork_ntimes(execinfo, execinfo->n_command);
	return (0);
}
