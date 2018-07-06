
//fs.h 



 
/*
 * partition_table_d:
 *     Structure for partition table.
 *
 */ 
struct partition_table_d
{    
	unsigned char boot_indicator; //80h active
    unsigned char start_chs[3];
    unsigned char partition_type;
    unsigned char end_chs[3];
    unsigned long start_sector;
    unsigned long partition_size; //in sectors.
	
};
struct partition_table_d *partition; 


//As informações na partition table apresentadas na forma de 'char'.  
struct partition_table_chars_d
{ 
	unsigned char BootFlag;                // Bootable or not
    
	unsigned char StartingCHS0;            // Not used
    unsigned char StartingCHS1;            // Not used
    unsigned char StartingCHS2;            // Not used
    
	unsigned char PartitionType;            // 
    
	unsigned char EndingCHS0;              // Not used
    unsigned char EndingCHS1;              // Not used
    unsigned char EndingCHS2;              // Not used
    
	unsigned char StartingSector0;       // Hidden sectors
    unsigned char StartingSector1;
    unsigned char StartingSector2;
    unsigned char StartingSector3;
    
	unsigned char PartitionLength0;      // Sectors in this partition
    unsigned char PartitionLength1;
    unsigned char PartitionLength2;
    unsigned char PartitionLength3; 
};
struct partition_table_chars_d *partition_chars; 



/*
typedef struct Fat16Entry_d Fat16Entry_t;
struct Fat16Entry_d 
{
    char           FileName[11];      // Filename + extension.
    unsigned char  Attr;              // File attributes.
    unsigned char  ReservedNT;        // Reserved for use by Windows NT.
    unsigned char  TimeInTenths;      // Millisecond stamp at file creation.
    unsigned short CreateTime;        // Time file was created.
    unsigned short CreateDate;        // Date file was created.
    unsigned short LastAccessDate;    // Date file was last accessed.
    unsigned short ClusterHigh;       // High word of this entry's start cluster.
    unsigned short Time;              // Time last modified.
    unsigned short Date;              // Date last modified.
    unsigned short ClusterLow;        // First cluster number low word.
    unsigned long  Size;              // File size. 
};
*/



/*
 * dir_entry_d:
 *     Entrada de diretório.
 *     @todo: Qual é o sistema de arquivos. ??!
 *     fat16

Structure of the Directory Entries
Offset	Size	 Description
  00h	8 bytes	 Filename
  08h	3 bytes	 Filename Extension
  0Bh	1 bytes	 Attribute Byte
  0Ch	1 bytes	 Reserved for Windows NT
  0Dh	1 bytes	 Creation - Millisecond stamp (actual 100th of a second)
  0Eh	2 bytes	 Creation Time
  10h	2 bytes	 Creation Date
  12h	2 bytes	 Last Access Date
  14h	2 bytes	 Reserved for FAT32
  16h	2 bytes	 Last Write Time
  18h	2 bytes	 Last Write Date
  1Ah	2 bytes	 Starting cluster
  1Ch	4 bytes	 File size in bytes
*/
typedef struct dir_entry_d dir_entry_t; 
struct dir_entry_d
{
    char           FileName[11];      // Filename + extension.
    unsigned char  Attr;              // File attributes.
    unsigned char  ReservedNT;        // Reserved for use by Windows NT.
    unsigned char  TimeInTenths;      // Millisecond stamp at file creation.
    unsigned short CreateTime;        // Time file was created.
    unsigned short CreateDate;        // Date file was created.
    unsigned short LastAccessDate;    // Date file was last accessed.
    unsigned short ClusterHigh;       // High word of this entry's start cluster.
    unsigned short Time;              // Time last modified.
    unsigned short Date;              // Date last modified.
    unsigned short ClusterLow;        // First cluster number low word.
    unsigned long  Size;              // File size.
};
//dir_entry_t *DirectoryEntry; 
//dir_entry_t *SystemDirectoryEntry;
//dir_entry_t *TmpDirectoryEntry; 
//...







