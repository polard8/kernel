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

int fcntl ( int fd, int cmd, long arg ){
	
	/*
	asm volatile (
		"movl $33, %%eax;"
	     	"movl %0, %%ebx;"
	     	"movl %1, %%ecx;"
		"movl %2, %%edx;"
	     	"int $0x80;" :: "g" (fd), "g" (cmd), "g" (arg) : "%eax", "%ebx", "%ecx", "%edx");

	// get return value 
	int *memptr = (int *) 0x9000;
	int *ret = memptr;

	return (int) *ret;
	*/
	
	return -1;
}

