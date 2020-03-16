



#include <stddef.h>
#include <types.h>
#include <sys/types.h>
#include <errno.h>

#include <sys/ioctl.h>
#include <sys/ioctls.h>

#include <termios.h>



/*
int
tcgetwinsize(int fd, struct winsize *ws)
{
	return ioctl(fd, TIOCGWINSZ, ws);
}
*/


pid_t tcgetpgrp ( int fd){

    int s;

    if ( ioctl(fd, TIOCGPGRP, &s) < 0 )
        return ((pid_t)-1);


    return ((pid_t) s);
}



int tcsetpgrp (int fd, pid_t pgrp){

    int s;
    s = pgrp;


    return ( ioctl(fd, TIOCSPGRP, &s) );
}



int tcgetattr (int fd, struct termios *termios_p){

    // TIOCGETA ?
    return ioctl (fd, TCGETS, termios_p);
}


int 
tcsetattr ( int fd, 
            int optional_actions,
            const struct termios *termios_p )
{
	switch ( optional_actions)
    {
        case TCSANOW:
            return ioctl (fd, TCSETS , termios_p);

        case TCSADRAIN:
            return ioctl (fd, TCSETSW, termios_p);

        case TCSAFLUSH:
            return ioctl (fd, TCSETSF, termios_p);
    };

    errno = EINVAL;

    return -1;
}


int tcsendbreak(int fd, int duration)
{ 
	return -1; 
}


int tcdrain (int fd)
{
    return ( ioctl(fd, TIOCDRAIN, 0) );
}


int tcflush (int fd, int queue_selector)
{ 
	return -1;
	
	/*
    int com;

	switch (queue_selector){

	case TCIFLUSH:
		com = FREAD;
		break;
	case TCOFLUSH:
		com = FWRITE;
		break;
	case TCIOFLUSH:
		com = FREAD | FWRITE;
		break;

	default:
		errno = EINVAL;
		return (-1);
	}
	return ( ioctl(fd, TIOCFLUSH, &com) );
	*/
}


int tcflow(int fd, int action)
{ 
    return -1; 
}


void cfmakeraw (struct termios *termios_p)
{

    if ( (void *) termios_p == NULL )
        return;

    termios_p->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP |
                             INLCR | IGNCR | ICRNL | IXON);


    termios_p->c_oflag &= ~OPOST;

    termios_p->c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);

    termios_p->c_cflag &= ~(CSIZE | PARENB);
    termios_p->c_cflag |= CS8;

    termios_p->c_cc[VMIN] = 1;
    termios_p->c_cc[VTIME] = 0;
}


speed_t cfgetispeed(const struct termios* tp)
{
    if ( (void *) tp == NULL )
        return 0;

    return tp->c_ispeed;
}




speed_t cfgetospeed(const struct termios* tp)
{
    if ( (void *) tp == NULL )
        return 0;

    return tp->c_ospeed;
}



int cfsetispeed(struct termios *termios_p, speed_t speed)
{
    if ( (void *) termios_p == NULL )
        return -1;

    return -1;
}


int cfsetospeed(struct termios *termios_p, speed_t speed)
{
    if ( (void *) termios_p == NULL )
        return -1;

	return -1;
}


int cfsetspeed(struct termios *termios_p, speed_t speed)
{
    if ( (void *) termios_p == NULL )
        return -1;

	return -1;
}





