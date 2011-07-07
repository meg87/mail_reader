#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

class Socket_c
{
	int sockfd;
	char buffer[2048];
	
public:
	bool Connect(char *address, char *port)
	{
		struct sockaddr_in serv_addr;
		struct hostent *server;

		/* Create a socket */
		sockfd = socket(AF_INET, SOCK_STREAM, 0);

		if (sockfd < 0) 
		{
			perror("ERROR opening socket");
			return false;
		}

		server = gethostbyname(address);

		if (server == NULL) 
		{
			fprintf(stderr,"ERROR, no such host\n");
			return false;
		}

		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET; // set address type to internet address
		bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
		serv_addr.sin_port = htons(atoi(port)); // set port

		/* Connect to server */
		if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) 
		{
			 perror("ERROR connecting");
			 return false;
		}
		else
			return true;
	}

	/* Send a request to server */
	int Send(char *msg, int len)
	{
		int n = write(sockfd, msg, len);

		if (n < 0) 
			 perror("ERROR writing to socket");

		return n;
	}

	/* Recive a response from server */
	char* Recive()
	{
		bzero(buffer, 2048);
		int n = read(sockfd, buffer, 2047);

		if (n < 0)
			 perror("ERROR reading from socket");

		return buffer;
	}
};
