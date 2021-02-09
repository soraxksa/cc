#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>


/*
struct hostent
{
  char *h_name;			// Official name of host.  
  char **h_aliases;		// Alias list.  
  int h_addrtype;		// Host address type.  
  int h_length;			// Length of address.  
  char **h_addr_list;		// List of addresses from name server. 
};
*/

int main()
{
	const char *hostname = "www.google.com";

	struct hostent *he;
	if( (he = gethostbyname(hostname)) == NULL)
	{
		printf("ERROR in gethostbyname()\n");
		return 0;
	}
	struct in_addr **addr_list = (struct in_addr**)he->h_addr_list;

	for(int i = 0; addr_list[i] != NULL; i++)
	{
		printf("addr_list[%d] = %s\n", i, inet_ntoa(*addr_list[i]));
	}
	printf("finished.\n");
	return 0;
}
