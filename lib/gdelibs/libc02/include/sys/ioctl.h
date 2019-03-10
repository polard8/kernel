
// No  single standard.  Arguments,	returns, and semantics of ioctl() vary
// according to the	device driver in question  (the	 call  is  used	 as  a
// catch-all  for  operations  that	 don't cleanly fit the UNIX stream I/O
// model).	See ioctl_list(2) for a	list of	 many  of  the	known  ioctl()
// calls.  The ioctl() function call appeared in Version 7 AT&T UNIX.
// comments credits: freebsd.org	 

int ioctl ( int d, int request, ... );


