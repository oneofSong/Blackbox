#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

	char path[100] = "/home/song/blackbox/";
	char *dirname;
	char *filename;

	strcat(path, "20180708_11/");
	dirname = strstr(path, "20180708_11/");
	printf("%s\n", path);

	strcpy(dirname, "20190708_12/");
	printf("%s\n", path);

	filename = strcat(path, "20180708_114452");
	printf("%s\n", path);
	

	filename = strstr(path, "20180708_114452");
	strcpy(filename, "20190708_120012");
	printf("%s\n", path);
	

	return 0;
}
