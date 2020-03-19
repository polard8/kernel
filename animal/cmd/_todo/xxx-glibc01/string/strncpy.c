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


#include <string.h>


char *strncpy (char *s1, const char *s2, size_t n){
	
  register char c;
  char *s = s1;

  --s1;

    if (n >= 4)
    {
        size_t n4 = n >> 2;

        for (;;)
        {
            c = *s2++;
            *++s1 = c;
        
            if (c == '\0')
                break;
            c = *s2++;
            *++s1 = c;
        
            if (c == '\0')
                break;
            c = *s2++;
            *++s1 = c;
        
            if (c == '\0')
                break;
            c = *s2++;
            *++s1 = c;
        
            if (c == '\0')
                break;
            if (--n4 == 0)
                goto last_chars;
        }
       
        n = n - (s1 - s) - 1;
        
        if (n == 0)
            return s;
        goto zero_fill;
    }

last_chars:
    
    n &= 3;
    
    if (n == 0)
        return s;

    do
    {
        c = *s2++;
        *++s1 = c;
        
        if (--n == 0)
            return s;
    
    } while (c != '\0');


zero_fill:
  
    do
    {
         *++s1 = '\0';
 
    } while (--n > 0);

    return s;
}

