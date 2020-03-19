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


#include <stdio.h>
#include <string.h>


//extern size_t strlen (const char *str);


//provisoria
//o tipo 'e size_t
int puts_strlen (const char *str)
{
	int ret_val;

	for(ret_val = 0; *str != '\0'; str++)
		ret_val ++;

	return ret_val;
}


/*
 *********************************************
 * puts:
 *     Uses the above routine to output a string...
 *     Uses putch.
 */

void puts (const char *text){
	
	/*
   	unsigned i = strlen (text);

	asm volatile (
		"movl $11, %%eax;"
	     	"movl %0, %%ebx;"
		"movl %1, %%ecx;"
		"movl $0, %%edx;"
	     	"int $0x80;" :: "b" (text), "g" (i) : "%eax", "%ecx", "%edx", "memory");	
	*/

	
	int i;
	
	//O tipo é 'size_t'.
	int l = puts_strlen (text);
	
	for (i=0; i < l; i++)
	{	
		putch ( (char) text[i] );
	};
}


