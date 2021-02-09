#include <stdio.h>


void usage(char *program_name)
{
	printf("Usage: %s <message> <# of time to repeat>\n", program_name);
	exit(0);	
}


int main(int argc, char **argv)
{
	int count = atoi(argv[2]);
	for(int i = 0; i < count; ++i)
	{
		printf("%3d - %s\n", i, argv[1]);
	}
}


