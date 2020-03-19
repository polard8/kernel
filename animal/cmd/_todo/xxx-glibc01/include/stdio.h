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


#ifndef _STDIO_H
#define _STDIO_H


/* file modes */
#define O_RDWR		0x1
#define O_RDONLY	0x2
#define O_WRONLY	0x4

/*
extern void putch (char c);
extern void puts (const char *text);
extern void printf (const char *fmt, ...);
extern void cls ();
extern unsigned char getch ();
extern unsigned char getkey ();
extern void gotoxy (int x, int y);
extern void setcolor (int t, int f);
extern int sprintf (char *buffer, const char *fmt, ...);
extern void beep (unsigned freq);
extern int open (const char *pathname, int flags);
extern int close (int fd);
extern int read (unsigned fd, void *buf, unsigned len);
*/

void putch (char c);
void puts (const char *text);

void printf (const char *fmt, ...);
//int printf(const char *fmt, ...);

void cls ();
unsigned char getch ();
unsigned char getkey ();
void gotoxy (int x, int y);
void setcolor (int t, int f);
int sprintf ( char *buffer, const char *fmt, ... );
void beep (unsigned freq);
int open (const char *pathname, int flags);
int close (int fd);
int read (unsigned fd, void *buf, unsigned len);

#endif
