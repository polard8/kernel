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


//http://man7.org/linux/man-pages/man3/psignal.3.html
//http://man7.org/linux/man-pages/man2/signal.2.html
//http://man7.org/linux/man-pages/man2/sigaction.2.html

#include <signal.h>


/* Uses the above routine to output a string... */
//void ( *signal(int signum, void (*handler)(int)) ) (int);

sighandler_t signal ( int signum, sighandler_t handler ){
	
	/*
	asm volatile ( " movl $27, %%eax; "
	               " movl %0, %%ebx;  "
		           " movl %1, %%ecx;  "
	               " int $0x80;       " :: "g" (signum), "g" (handler) : "%eax", "%ebx", "%ecx" );

	return handler;
	*/
	
	//todo
	
	return 0;
}

