#include        <sys/time.h>
#include        <sys/types.h>
#include        <sys/socket.h>
#include        <netinet/in.h>
#include        <errno.h>
#include        <netdb.h>
#include        <pthread.h>
#include        <signal.h>
#include        <stdlib.h>
#include        <stdio.h>
#include        <string.h>
#include        <semaphore.h>
#include        <unistd.h>
#include        "socketutil.h"

#define PORT            "3000"

// UDP datagram unicast test program

int
main( int argc, char ** argv )
{
	struct addrinfo		addrinfo;
	struct addrinfo *	result;
	int			sd;
	struct sockaddr_in *	sockaddr_ptr;
	int			len;
	char			buffer[512];
	char			prompt[] = "Enter a string>>";
	const char *		func = "main";

	addrinfo.ai_flags = 0;
	addrinfo.ai_family = AF_INET;		
	addrinfo.ai_socktype = SOCK_DGRAM;	// I want connectionless datagrams
	addrinfo.ai_protocol = 0;
	addrinfo.ai_addrlen = 0;
	addrinfo.ai_addr = NULL;
	addrinfo.ai_canonname = NULL;
	addrinfo.ai_next = NULL;
	if ( argc < 2 )
	{
		printf( "\x1b[2;31mMust specify receiver machine on command line.\x1b[0m\n" );
		return -1;
	}
	else if ( getaddrinfo( argv[1], PORT, &addrinfo, &result ) != 0 )
	{
		printf( "getaddrinfo() failed in %s()\n", func );
		return -1;
	}
	else if ( (sd = socket( result->ai_family, result->ai_socktype, result->ai_protocol )) == -1 )
	{
		freeaddrinfo( result );
		printf( "socket() failed in %s()\n", func );
		return -1;
	}
	else
	{
		sockaddr_ptr = (struct sockaddr_in *)(result->ai_addr);
		printf( "datagram target is %s port %d\n", get_istring( ntohl( sockaddr_ptr->sin_addr.s_addr ),
			buffer, sizeof(buffer) ), ntohs( sockaddr_ptr->sin_port ) );
		while ( write( 1, prompt, sizeof(prompt) ), (len = read( 0, buffer, sizeof(buffer) )) > 0 )
		{
			buffer[ len-1 ] = '\0';
			printf( "%s now sending buffer to receiver\n", argv[0] );
			errno = 0;
			if ( sendto( sd, buffer, len, 0, (struct sockaddr *)sockaddr_ptr, sizeof(*sockaddr_ptr )) < 0 )
			{
				printf( "\x1b[2;31msendto() failed file %s line %d errno %d %s\x1b[0m\n", __FILE__,
					__LINE__ , errno, strerror(errno) );
				freeaddrinfo( result );
				return -1;
			}
		}
		freeaddrinfo( result );
		printf( "Normal end of %s\n", argv[0] );
		return 0;
	}
}
