/*
 *  ZeX/OS
 *  Copyright (C) 2007  Tomas 'ZeXx86' Jedrzejek (zexx86@gmail.com)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


//#importante
//Os serviços atendidos pela system call para socket da libc vao de 7000 `a 7999.


#include <string.h>
#include <sys/socket.h>



/*
//?? domain, type, protocol
socket() creates an endpoint for communication and returns a file
       descriptor that refers to that endpoint.  The file descriptor
       returned by a successful call will be the lowest-numbered file
       descriptor not currently open for the process.
	   
The domain argument specifies a communication domain; this selects
       the protocol family which will be used for communication.  These
       families are defined in <sys/socket.h>. 
	 
The socket has the indicated type, which specifies the communication
       semantics.
*/
		   
int socket ( int family, int type, int protocol ){
	
	/*
	asm volatile ( "movl $12, %%eax;"
	     	"movl %0, %%ebx;"
	     	"movl %1, %%ecx;"
	     	"movl %2, %%edx;"
	     	"int $0x80;" :: "g" (family), "g" (type), "g" (protocol) : "%eax", "%ebx", "%ecx", "%edx");

	//get return value

	int *memptr = (int *) 0x9000;
	int *ret = memptr;

	return (int) *ret;
	*/
	
    //serviço 7000.
	return (int) system_call ( 7000, (unsigned long) family, (unsigned long) type, (unsigned long) protocol );
}

