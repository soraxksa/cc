#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../debug/hacking.h"


#define PORT 7890

int main(void)
{
	int sockfd, new_sockfd;
	struct sockaddr_in host_addr, client_addr;
	socklen_t sin_size;
	int recv_length=1, yes=1;
	char buffer[1024];

	if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		fatal("in socket()\n");
	}

	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
	{
		fatal("setting socket option SO_REUSEADDR\n");
	}

	host_addr.sin_family      = AF_INET;
	host_addr.sin_port        = htons(PORT);
	host_addr.sin_addr.s_addr = 0;

	if(bind(sockfd, (struct sockaddr*)&host_addr, sizeof(struct sockaddr)) == -1)
		fatal("in bind()\n");

	if(listen(sockfd, 5) == -1)
		fatal("listen()\n");


	printf("server: got socket from %s port %d\n", inet_ntoa(host_addr.sin_addr), ntohs(host_addr.sin_port));

	while(1)
	{
		sin_size = sizeof(struct sockaddr_in);
		new_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &sin_size);
		if(new_sockfd == -1)
			fatal("accept()\n");

		printf("server: got connection from %s port %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		send(new_sockfd, "Hello, client\n", 13, 0);
		recv_length = recv(new_sockfd, &buffer, 1024, 0);
		while(recv_length > 0)
		{
			printf("RECV: %d bytes\n", recv_length);
			dump(buffer, recv_length);
			recv_length = recv(new_sockfd, &buffer, 1024, 0);
		}
		close(new_sockfd);
	}

	return 0;

}
