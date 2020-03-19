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


#ifndef __STRING_H
#define	__STRING_H


#include <_size_t.h>
#include <_null.h>

extern void *memcpy(void *dst_ptr, const void *src_ptr, size_t count);
extern void *memsetw(void *dst, int val, size_t count);
extern void *memset(void *dst, int val, size_t count);
extern size_t strlen(const char *str);
extern char *strcpy(char *to, const char *from);
extern char *strcat(char *s, const char *add);
extern int strcmp(const char *cs, const char *ct);
extern int strncmp(const char *cs, const char *ct, size_t count);

#endif

