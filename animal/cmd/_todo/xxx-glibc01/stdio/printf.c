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
#include <stdarg.h>
#include <string.h>
#include <_printf.h>


extern size_t strlen (const char *str);


static int printf_help (unsigned c, void **ptr)
{
	//putch (c);
	putch ( (char) c );

	return 0;
}


void printf ( const char *fmt, ... ){
	
	va_list args;
	va_start (args, fmt);
	
	(void) do_printf (fmt, args, printf_help, NULL);
	
	va_end (args);
}


