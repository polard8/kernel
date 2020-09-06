

// sys/spawn.h
  

#ifndef _SYS_SPAWN_H_
#define _SYS_SPAWN_H_



struct posix_spawnattr 
{
	short			sa_flags;
	pid_t			sa_pgroup;
	
	//#todo
	//struct sched_param	sa_schedparam;
	
	int			    sa_schedpolicy;
	
	//#todo
	//sigset_t		sa_sigdefault;
	//sigset_t		sa_sigmask;
};


struct posix_spawn_file_actions 
{
    unsigned int size;	/* size of fae array */
    unsigned int len;	/* how many slots are used */

	//#todo
	//posix_spawn_file_actions_entry_t *fae;
};


typedef struct posix_spawnattr           posix_spawnattr_t;
typedef struct posix_spawn_file_actions  posix_spawn_file_actions_t;

#define POSIX_SPAWN_RESETIDS		0x01
#define POSIX_SPAWN_SETPGROUP		0x02
#define POSIX_SPAWN_SETSCHEDPARAM	0x04
#define POSIX_SPAWN_SETSCHEDULER	0x08
#define POSIX_SPAWN_SETSIGDEF		0x10
#define POSIX_SPAWN_SETSIGMASK		0x20



#endif    


