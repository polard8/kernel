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
#include <stdlib.h>
#include <sys/socket.h>


hostent *gethostbyname (char *hostname){
	
	unsigned l = strlen (hostname);

	hostent *host = (hostent *) malloc (sizeof (hostent));
	memset (host, 0, sizeof (hostent));

	host->h_addr = (char *) malloc (sizeof (char) * l + 2);
	memset (host->h_addr, 0, l+1);

	memcpy (host->h_addr, hostname, l);
	host->h_addr[l] = '\0';

	/* +1 ? Yes, it contain zero character '\0' because memcpy */
	host->h_length = l+1;

	return host;
}


 
