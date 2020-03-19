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

char *itoa (int value, char *string, int radix)
{
	char buf[16];
	char * where = buf + 16 - 1;
	*where = '\0';

	do
	{
		unsigned long temp = (unsigned long)value % radix;
		where--;
		if(temp < 10)
			*where = temp + '0';
		else
			*where = temp - 10 + 'a';
		value = (unsigned long)value / radix;
	}
	while(value != 0);

	unsigned l = strlen (where);
	memcpy (string, where, l);
	string [l] = '\0';

	return string;
}
