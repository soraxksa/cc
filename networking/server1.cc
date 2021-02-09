#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <pthread.h>

void* connection_handler(void *);

int main()
{
	int sockfd, new_sockfd, sockaddr_len, *thread_sockfd;
	struct sockaddr_in server, clinet;

	//create socket for this computer
	if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("ERROR in socket()\n");
		return 0;
	}
	printf("sockfd done.\n");

	//info for what we want
	server.sin_family      = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port        = htons(6969);
                               
	//bind the info with the socket
	if( bind(sockfd,(struct sockaddr*)&server, sizeof(server)) < 0)
	{
		printf("ERROR in bind\n");
		return 0;
	}	         
	printf("bind done.\n");

	//make the socket listen in its thread of execution
	listen(sockfd, 3);

	printf("Waiting for incoming connections...\n");
	sockaddr_len = sizeof(struct sockaddr_in);
	//if socket thread accepted a connection then continue 
	while( new_sockfd = accept(sockfd, (struct sockaddr*)&clinet, (socklen_t*)&sockaddr_len))
	{
		printf("Connection accepted.\n");
		const char *msg =  "Hello friend, i'm the server\ni will assign a handler for you\n";
		write(new_sockfd, msg, strlen(msg));


		pthread_t sniffer_thread;
		thread_sockfd  = (int*)malloc(4);
		*thread_sockfd = new_sockfd;

		if(pthread_create(&sniffer_thread, NULL, connection_handler, (void*)thread_sockfd) < 0)
		{
			printf("ERROR in pthread_create()\n");
			return 0;
		}                

		printf("Handler assigned.");

	}

	if(new_sockfd < 0)
	{
		printf("ERROR in accept()\n");
		return 0;
	}


	close(sockfd);

	return 0;
}


void* connection_handler(void *socket_fd)
{
	int sock_fd = *(int*)socket_fd;
	int read_size;
	char clinet_message[1024];

	const char* msg1 = "Greetings! I am your connection handler\n";
	write(sock_fd, msg1, strlen(msg1));

	const char *msg2 = "Now type something and i shall repeat what you typed\n";
	write(sock_fd, msg2, strlen(msg2));

	while( (read_size = recv(sock_fd, clinet_message, 2000, 0)) > 0)
	{
		write(sock_fd, clinet_message, strlen(clinet_message));
	}
	if(read_size == 0)
	{
		printf("Client disconnected\n");
		//fflash(stdout);
	}

	if(read_size < 0)
	{
		printf("ERROR in recv\n");
	}

	free(socket_fd);
	return 0;
}




