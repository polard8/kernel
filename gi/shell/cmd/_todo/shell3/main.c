/* Compile with: g++ -Wall –Werror -o shell shell.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
 
#include <sys/types.h>
#include <sys/wait.h>
 
/* The array below will hold the arguments: args[0] is the command. */
static char* args[512];
pid_t pid;
int command_pipe[2];
 
#define READ  0
#define WRITE 1
 
/*
 * Handle commands separatly
 * input: return value from previous command (useful for pipe file descriptor)
 * first: 1 if first command in pipe-sequence (no input from previous pipe)
 * last: 1 if last command in pipe-sequence (no input from previous pipe)
 *
 * EXAMPLE: If you type "ls | grep shell | wc" in your shell:
 *    fd1 = command(0, 1, 0), with args[0] = "ls"
 *    fd2 = command(fd1, 0, 0), with args[0] = "grep" and args[1] = "shell"
 *    fd3 = command(fd2, 0, 1), with args[0] = "wc"
 *
 * So if 'command' returns a file descriptor, the next 'command' has this
 * descriptor as its 'input'.
 */
static int command(int input, int first, int last)
{
	int pipettes[2];
 
	/* Invoke pipe */
	pipe( pipettes );	
	pid = fork();
 
	/*
	 SCHEME:
	 	STDIN --> O --> O --> O --> STDOUT
	*/
 
	if (pid == 0) {
		if (first == 1 && last == 0 && input == 0) {
			// First command
			dup2( pipettes[WRITE], STDOUT_FILENO );
		} else if (first == 0 && last == 0 && input != 0) {
			// Middle command
			dup2(input, STDIN_FILENO);
			dup2(pipettes[WRITE], STDOUT_FILENO);
		} else {
			// Last command
			dup2( input, STDIN_FILENO );
		}
 
		if (execvp( args[0], args) == -1)
			_exit(EXIT_FAILURE); // If child fails
	}
 
	if (input != 0) 
		close(input);
 
	// Nothing more needs to be written
	close(pipettes[WRITE]);
 
	// If it's the last command, nothing more needs to be read
	if (last == 1)
		close(pipettes[READ]);
 
	return pipettes[READ];
}
 
/* Final cleanup, 'wait' for processes to terminate.
 *  n : Number of times 'command' was invoked.
 */
static void cleanup(int n)
{
	int i;
	for (i = 0; i < n; ++i) 
		wait(NULL); 
}
 
static int run(char* cmd, int input, int first, int last);
static char line[1024];
static int n = 0; /* number of calls to 'command' */
 
int main()
{
	printf("SIMPLE SHELL: Type 'exit' or send EOF to exit.\n");
	
	while (1){
		
		/* Print the command prompt */
		printf("$> ");
		
		//isso falhou. #todo checar fflush com argumento NULL.
		//fflush(NULL);
         //fflush(stdout);
 
		/* Read a command line */
		//if (!fgets(line, 1024, stdin)) 
			//return 0;
			
		gets (line);
 
		int input = 0;
		int first = 1;
 
		char* cmd = line;
		char* next = strchr(cmd, '|'); /* Find first '|' */
 
		while (next != NULL) {
			/* 'next' points to '|' */
			*next = '\0';
			input = run(cmd, input, first, 0);
 
			cmd = next + 1;
			next = strchr(cmd, '|'); /* Find next '|' */
			first = 0;
		}
		input = run(cmd, input, first, 1);
		cleanup(n);
		n = 0;
	}
	return 0;
}
 
static void split(char* cmd);
 
static int run(char* cmd, int input, int first, int last)
{
	split(cmd);
	if (args[0] != NULL) {
		if (strcmp(args[0], "exit") == 0) 
			exit(0);
		n += 1;
		return command(input, first, last);
	}
	return 0;
}
 
static char* skipwhite(char* s)
{
	while (isspace(*s)) ++s;
	return s;
}
 
static void split(char* cmd)
{
	cmd = skipwhite(cmd);
	char* next = strchr(cmd, ' ');
	int i = 0;
 
	while(next != NULL) {
		next[0] = '\0';
		args[i] = cmd;
		++i;
		cmd = skipwhite(next + 1);
		next = strchr(cmd, ' ');
	}
 
	if (cmd[0] != '\0') {
		args[i] = cmd;
		next = strchr(cmd, '\n');
		next[0] = '\0';
		++i; 
	}
 
	args[i] = NULL;
}
