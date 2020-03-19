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

int atoi (const char *s)
{
    char ** endptr = /*(char **) */&s;
    int base = 10;

    int nDigit;
    int acc = 0;

    while((nDigit = *s) != 0)
    {
        // Convert to digit
        nDigit -= '0';
        if(nDigit > 9)
            nDigit -= ('A' - '9' - 1);
        if(nDigit > base - 1)
            break;

        // Move the value to the next rank and add the digit
        acc *= base;
        acc += nDigit;
        s ++;
    }

    if(endptr != 0)
        *endptr = (char *) s;

    return acc;
}
