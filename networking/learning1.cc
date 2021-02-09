#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


/*
// IPv4 AF_INET sockets:
struct sockaddr_in {
    short            sin_family;   // e.g. AF_INET, AF_INET6
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
};

struct in_addr {
    unsigned long s_addr;          // load with inet_pton()
};

struct sockaddr {
    unsigned short    sa_family;    // address family, AF_xxx
    char              sa_data[14];  // 14 bytes of protocol address
};
*/

#define MAXINPUT 10000

int main()
{
	int sockfd;
	struct sockaddr_in server;
	char *output, input[MAXINPUT];

	if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("ERRER in socket()\n");
		return 0;
	}

	server.sin_family      = AF_INET;
	server.sin_addr.s_addr = inet_addr("216.239.38.120");
	server.sin_port        = htons(80);

	int con;
	if( (con = connect(sockfd, (struct sockaddr*)&server, sizeof(server))) < 0)
	{
		printf("ERROR in connect()\n");
		return 0;
	}
	printf("connect:%d\n", con);
	printf("connected.\n");

	int sen;
	output = "GET / HTTP/1.1\r\n\r\n";
	if( (sen = send(sockfd, output, strlen(output), 0)) < 0)
	{
		printf("ERROR in send()\n");
		return 0;
	}
	printf("send:%d\n", sen);
	printf("data send\n");

	unsigned rec;
	if((rec = recv(sockfd, input, MAXINPUT, 0)) < 0)
	{
		printf("ERROR in recv\n");
		return 0;
	}
	printf("recv:%u\n");
	printf("server respond\n%s", input);

	close(sockfd);

	return 0;
}









