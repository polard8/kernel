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


#ifndef _VFS_H
#define _VFS_H

#define VFS_FILEATTR_FILE	0x1
#define VFS_FILEATTR_DIR	0x2
#define VFS_FILEATTR_HIDDEN	0x4
#define VFS_FILEATTR_SYSTEM	0x8
#define VFS_FILEATTR_BIN	0x10
#define VFS_FILEATTR_READ	0x20
#define VFS_FILEATTR_WRITE	0x40
#define VFS_FILEATTR_MOUNTED	0x80

#define VFS_FILENAME_LEN	10
#define VFS_MOUNTPOINT_LEN	32


/* Virtual filesystem structure */
typedef struct vfs_context {
  struct vfs_context *next, *prev;

  char *name;
  char mountpoint[VFS_MOUNTPOINT_LEN];
  unsigned attrib;
  char *ptr;
} vfs_t;


extern int mount (const char *devname, const char *mountpoint);

#endif
