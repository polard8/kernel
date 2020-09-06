

#ifndef _SPAWN_H_
#define _SPAWN_H_


#include <sys/spawn.h>


int 
posix_spawn (
    pid_t *pid, 
    const char *path,
    const posix_spawn_file_actions_t *file_actions,
    const posix_spawnattr_t *attrp,
    char *const argv[], 
    char *const envp[] );
    
    
int 
posix_spawnp (
    pid_t *pid, 
    const char *file,
    const posix_spawn_file_actions_t *file_actions,
    const posix_spawnattr_t *attrp,
    char *const argv[], 
    char *const envp[] );
    
    

#endif	/* _SPAWN_H_ */


