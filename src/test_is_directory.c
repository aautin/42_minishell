#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	struct stat	path_stat;

	for (int i = 1; i < argc; i++)
	{
		char *path = argv[i];
		stat(path, &path_stat);
		printf("%s-->%d\n", path, S_ISDIR(path_stat.st_mode));
	}
	return 0;
}
