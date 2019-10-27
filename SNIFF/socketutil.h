#ifndef socketutil_h
#define socketutil_h

#include	<netinet/in.h>
#include	<sys/socket.h>
#include	<netdb.h>

long		get_iaddr( const struct sockaddr_in );
int		get_port( const struct sockaddr_in );
void		set_iaddr( struct sockaddr_in, long, unsigned int );
void		set_iaddr_str( struct sockaddr_in, char *, unsigned int );
long		get_host_addr( char * );
char *		get_istring( unsigned long, char *, unsigned int );
long		get_iaddr_string( char * );
int		get_selfip( char *, char *, int );
void		print_addrinfo( struct addrinfo * );

#endif
