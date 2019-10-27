sudo ./capture5 eth0

This is how you run it.
gcc -o capture5 -I. capture5.c libpcap.a

This is how you compile it.
cd libpcap-1.9.0

You need to do "./configure" alot will text will show then just type make. 
That is how the "libpcap.a" is made, you also need to be in the "libpcap-1.9.0" directory 
so "cd libpcap-1.9.0" first.

./configure
make