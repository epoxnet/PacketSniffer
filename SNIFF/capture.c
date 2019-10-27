//Network Security 3-12 (capture)

#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static const char *
get_pcap_error( int result)
{
        switch ( result )
        {
                case PCAP_ERROR_ACTIVATED:
                        return "PCAP_ERROR_ACTVATED";
                case PCAP_ERROR_NO_SUCH_DEVICE:
                        return "PCAP_ERROR_NO_SUCH_DEVICE";
                case PCAP_ERROR_PERM_DENIED:
                        return "PCAP_ERROR_PERM_DENIED";
                case PCAP_ERROR_PROMISC_PERM_DENIED:
                        return "PCAP_ERROR_ROMISC_PERM_DENIED";
                case PCAP_ERROR_RFMON_NOTSUP:
                        return "PCAP_ERROR_RFMON_NOTSUP";
                case PCAP_ERROR_IFACE_NOT_UP:
                        return "PCAP_ERROR_IFACE_NOT_UP";
                case PCAP_ERROR:
                        return "PCAP_ERROR";
                default:
                        return "UNKOWN ERROR";
        }
}


int
main (int argc, char ** argv)
{
        char                            errbuf[PCAP_ERRBUF_SIZE];
        pcap_t *                        p;
        int                             result;
        const unsigned char *           s;
        struct pcap_pkthdr              header;        char *                          hexptr;        //Vector                        vector( 200 );            //this is c++ code        struct bpf_program              program;        int                             header_type;
        if ( argc <2 )        {                fprintf ( stderr, "\x1b[1;31mMust specify device name on command line.\n\x1b[0m");                return 1;        }        else if ( ( p = pcap_create (argv[1], errbuf)) == 0 )        {                fprintf (stderr, "\x1b[1;31mpcap_create() failed file %s line %d. \n\x1b[0m",                        __FILE__,__LINE__);                return 1;        }        else if ((result = pcap_activate ( p )) != 0)        {                fprintf( stderr, "\x1b[1'31mpcap_activate() failed result %s file %s line %d.\n\x1b[0m",                       get_pcap_error ( result ), __FILE__,__LINE__);
                return 1;
        }
        else if (pcap_compile(p, &program, "port 4000", 0, PCAP_NETMASK_UNKNOWN) !=0)
        {
                fprintf(stderr, "\x1b[1;31mpcap_compile() failed esult %s file %s line %d.\n\x1b[0m",
                                pcap_geterr(p),__FILE__,__LINE__);
                return 1;
        }
        else if (pcap_setfilter (p, &program) != 0 )
        {
                fprintf( stderr, "\x1b[1;31mpcap_setfilter() failed resilt %s file %s line %d.\n\x1b[0m",
                        pcap_geterr(p),__FILE__,__LINE__);
                return 1;
        }
        else
        {
                header_type = pcap_datalink (p);
                //fprinf (stdout, " //Brian put the code away
                pcap_freecode (&program);
               while ( ( s = pcap_next( p, &header )) !=0)
                {
                        //hexptr = get_hex_string ( s, header.caplen, vector);
                        //fprintf (stdout, " \x1b[1;32nCaptured packet legth %d %s \n\n\x1b[0m", header.len, hexpt$
                        for ( int i = 0 ; i < (header.len-66) ; i++)
                        {
                                fprintf (stdout, "%c" ,*(s+66+i));
                        }
                        fprintf (stdout, "\n");
                }
                pcap_close( p );
                fprintf (stderr, "\x1b[1;32mIt's all good.\n\x1b[0m");
                return 0;
        }
}