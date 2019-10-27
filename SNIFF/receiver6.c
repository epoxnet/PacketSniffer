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
#include	"socketutil.h"

#define PORT            "3000"

// UDP datagram receiver test program.  sender6 works with receiver6.

int
main( int argc, char ** argv )
{
	struct addrinfo		addrinfo;
	struct addrinfo *	result;
	int			on = 1;
	int			sd;
	socklen_t		sz;
	struct sockaddr_in	addr;
	int			len;
	char			buffer[512];
	char			ipstring[20];
	char			origin[40];
	const char *		func = "main";

	addrinfo.ai_flags = AI_PASSIVE;
	addrinfo.ai_family = AF_INET;		
	addrinfo.ai_socktype = SOCK_DGRAM;
	addrinfo.ai_protocol = 0;
	addrinfo.ai_addrlen = 0;
	addrinfo.ai_addr = NULL;
	addrinfo.ai_canonname = NULL;
	addrinfo.ai_next = NULL;
        if ( getaddrinfo( 0, PORT, &addrinfo, &result ) != 0 )
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
	else if ( setsockopt( sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) ) == -1 )
	{
		freeaddrinfo( result );
		printf( "setsockopt() failed in %s()\n", func );
		return -1;
	}
	else if ( errno = 0, bind( sd, result->ai_addr, result->ai_addrlen ) == -1 )
	{
		freeaddrinfo( result );
		printf( "bind() failed in %s() line %d errno %d\n", func, __LINE__, errno );
		close( sd );
		return -1;
	}
	else
	{
		freeaddrinfo( result );
		sz = sizeof( addr );
		get_selfip( "enp0s31f6", ipstring, sizeof(ipstring) );
		printf( "%s at %s port %s ready to receive packets...\n", argv[0], ipstring, PORT );
		while ( (len = recvfrom( sd, buffer, sizeof(buffer), 0, (struct sockaddr *)&addr, &sz )) > 0 )
		{
			printf( "received following message from %s port %d:\n",
				get_istring( ntohl( addr.sin_addr.s_addr ), origin, sizeof(origin) ), ntohs( addr.sin_port ) );
			printf( "%s\n", buffer );
		}
		printf( "Execution end of %s len is %d\n", argv[0], len );
		return 0;
	}
}
