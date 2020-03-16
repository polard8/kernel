



#include <termios.h>
#include <errno.h>
#include <sys/ioctls.h>
#include <sys/ioctl.h>


/*
pid_t tcgetpgrp ( int fd);
pid_t tcgetpgrp ( int fd){
	
	int s;

	if (ioctl(fd, TIOCGPGRP, &s) < 0)
		return ((pid_t)-1);

	return ((pid_t)s);
}
*/

/*
int tcsetpgrp (int fd, pid_t pgrp);
int tcsetpgrp (int fd, pid_t pgrp){
	
	int s;
	s = pgrp;
	
	return ( ioctl(fd, TIOCSPGRP, &s) );
}
*/

int tcgetattr (int fd, struct termios *termios_p){

    //return ioctl (fd, TIOCGETA, termios_p);
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


// Credits: Apple open source.
/*
int
tcsetattr(fd, opt, t)
	int fd, opt;
	const struct termios *t;
{
	struct termios localterm;

	if (opt & TCSASOFT) {
		localterm = *t;
		localterm.c_cflag |= CIGNORE;
		t = &localterm;
	}
	switch (opt & ~TCSASOFT) {
	case TCSANOW:
		return (ioctl(fd, TIOCSETA, t));
	case TCSADRAIN:
		return (ioctl(fd, TIOCSETAW, t));
	case TCSAFLUSH:
		return (ioctl(fd, TIOCSETAF, t));
	default:
		errno = EINVAL;
		return (-1);
	}
} 
*/


int tcsendbreak(int fd, int duration)
{ 
	return -1; 
}


int tcdrain (int fd)
{
	return -1; 
	//return ( ioctl(fd, TIOCDRAIN, 0) );
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
    return tp->c_ispeed;
}


speed_t cfgetospeed(const struct termios* tp)
{
    return tp->c_ospeed;
}

int cfsetispeed(struct termios *termios_p, speed_t speed)
{
    return -1;
}


int cfsetospeed(struct termios *termios_p, speed_t speed)
{
	return -1;
}


int cfsetspeed(struct termios *termios_p, speed_t speed)
{
	return -1;
}





