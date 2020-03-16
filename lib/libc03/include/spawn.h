#ifndef	_SPAWN_H_
#define	_SPAWN_H_

//posix_spawn , posix_spawnp

#define POSIX_SPAWN_RESETIDS		0x01
#define POSIX_SPAWN_SETPGROUP		0x02
#define POSIX_SPAWN_SETSCHEDPARAM	0x04
#define POSIX_SPAWN_SETSCHEDULER	0x08
#define POSIX_SPAWN_SETSIGDEF		0x10
#define POSIX_SPAWN_SETSIGMASK	0x20

/*
 * Spawn routines
 *
 * XXX both arrays should be __restrict, but this does not work when GCC
 * is invoked with -std=c99.
 */
/*
int posix_spawn(pid_t *__restrict, const char *__restrict,
    const posix_spawn_file_actions_t *, const posix_spawnattr_t *__restrict,
    char *const [], char *const []);
int posix_spawnp(pid_t *__restrict, const char *__restrict,
    const posix_spawn_file_actions_t *, const posix_spawnattr_t *__restrict,
char *const [], char *const []);
*/

#endif	/* _SPAWN_H_ */


