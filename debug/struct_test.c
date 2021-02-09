#include <stdio.h>

struct foo{
	int id;
	int data;
	int len;
};

void print_struct(struct foo A)
{
	printf("[A.id] = %d\n", A.id);
}


int main()
{
	struct foo A = {999, 0x41, 0x69};
	print_struct(A);
}

