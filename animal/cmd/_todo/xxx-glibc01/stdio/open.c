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

//system calls.
#include <stubs/gramado.h> 

int open (const char *pathname, int flags){
	
	/*
	asm volatile (
		"movl $18, %%eax;"
	     	"movl %0, %%ebx;"
		"movl %1, %%ecx;"
	     	"int $0x80;" :: "b" (pathname), "g" (flags) : "%eax", "%ecx", "memory");

	int *memptr = (int *) 0x9000;
	int *fd = memptr;

	return *fd;
	*/
	
	//precisa ser assim.
	//return (int) gramado_system_call ( 16, (unsigned long) pathname, (unsigned long) flags, (unsigned long) mode );
	
	//vamos improvisar por enquanto.
	return (int) gramado_system_call ( 16, (unsigned long) pathname, 
				     (unsigned long) flags, (unsigned long) 0 );	
}





