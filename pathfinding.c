#include "includes.h"

/**
 * get_file_path - get directory from PATH if it contains a file
 * @filename: filename to check for full path
 * Return: 1 on sucess, 0 on fail
 */

char *get_file_path(char *filename)
{
	DIR *directory;
	struct dirent *dint;
	int i;
	const char delim[] = ":";
	char *path;
	char **paths;

	path = _getenv("PATH");
	paths = sherlock(path, delim);

	for (i = 0; paths[i] != NULL; i++)
	{
		directory = opendir(paths[i]);
		while ((dint = readdir(directory)))
		{
			if (_strcmp(dint->d_name, ".") == 0
			    || _strcmp(dint->d_name, "..") == 0)
				continue;
			else if (strcmp(dint->d_name, filename) == 0)
			{
				filename = dircat(paths[i], filename);
				if (filename == NULL)
				{
					printf("error could not concatonate\n");
				}
				closedir(directory);
				free_d_ptr(paths);
				return (filename);
			}
		}
		closedir(directory);
	}
	free_d_ptr(paths);
	return (NULL);
}
