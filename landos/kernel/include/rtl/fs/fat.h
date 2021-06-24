

#ifndef  __FAT_H
#define  __FAT_H    1


// definições, variáveios, estruturas e protótipos
// específicos para o sistema de arquivos fat16.
// Isolando pra talvez tirarmos isso do kernel.
// fat16 é o sistema da partição de boot apenas.


// fat16 file attributes.
// See:
// https://en.wikipedia.org/wiki/Design_of_the_FAT_file_system

#define FAT_FILE_FLAG_READ              0x01
#define FAT_FILE_FLAG_HIDDEN            0x02
#define FAT_FILE_FLAG_SYSTEM            0x04   //HARDWARE.
#define FAT_FILE_FLAG_VOLUME_LABEL      0x08

#define FAT_FILE_FLAG_DIRECTORY         0x10
#define FAT_FILE_FLAG_FILE              0x20
#define FAT_FILE_FLAG_DEVICE            0x40   
#define FAT_FILE_FLAG_RESERVED          0x80

//
// FAT definitions.
//

//#define FAT_SECTOR_SIZE                 512
//#define FAT_FIRST_DATA_CLUSTER          2

//#define FAT16_CLUSTER_MASK              0xFFFF
//#define FAT16_LINK_TERMINATOR           0xFFFF

//#define FAT32_CLUSTER_MASK              0x0FFFFFFF
//#define FAT32_LINK_TERMINATOR           0x0FFFFFFF


#define	FAT12_MASK	0x00000fff	/* mask for 12 bit cluster numbers */
#define	FAT16_MASK	0x0000ffff	/* mask for 16 bit cluster numbers */
#define	FAT32_MASK	0x0fffffff	/* mask for FAT32 cluster numbers */


#define  FAT16_CLUSTER_AVAILABLE    0x0000
#define  FAT16_CLUSTER_RESERVED     0xfff0
#define  FAT16_CLUSTER_BAD          0xfff7
#define  FAT16_CLUSTER_LAST         0xffff



#define FAT_DIRECTORY_ENTRY_FREE        0xE5
#define FAT_DIRECTORY_ENTRY_LAST        0x00

/*
#define FAT_DIRECTORY_ENTRY_FREE        0xE5
#define FAT_DIRECTORY_ENTRY_LAST        0x00

#define FAT_ATTRIBUTE_READ_ONLY         0x01
#define FAT_ATTRIBUTE_HIDDEN            0x02
#define FAT_ATTRIBUTE_SYSTEM            0x04
#define FAT_ATTRIBUTE_VOLUME_ID         0x08
#define FAT_ATTRIBUTE_DIRECTORY         0x10
#define FAT_ATTRIBUTE_ARCHIVE           0x20
#define FAT_ATTRIBUTE_LONG_NAME         (FAT_ATTRIBUTE_READ_ONLY | FAT_ATTRIBUTE_HIDDEN | FAT_ATTRIBUTE_SYSTEM | FAT_ATTRIBUTE_VOLUME_ID)
#define FAT_ATTRIBUTE_MASK              0x3F

#define FAT_LONG_NAME_TERMINATOR        0x40
#define FAT_LONG_NAME_ORDER_MASK        0x3F
*/

//#define FAT_MAX_PATH                    255



// fat16 support.
#define FAT16_ROOT_ENTRIES  512  // 512 entradas no rootdir. 
#define FAT16_ENTRY_SIZE    32   // Tamanho em bytes da entrada no root dir. 
#define FAT_ERRO_1    0xffff9 
#define FAT_ERRO_2    0xffff8
#define FAT_ERRO_3    0xffff7
#define FAT_ERRO_4    0xffff6
#define FAT_STATUS_1  0xffff5
#define FAT_STATUS_2  0xffff4
#define FAT_STATUS_3  0xffff3
#define FAT_STATUS_4  0xffff2
#define ENTRY_NEVER_USED       0x00
#define ENTRY_FILE_IS_DELETED  0xE5 
#define ENTRY_DIRECTORY        0x2E 
#define FILE_ATTRIBUTE_READ_ONLY     0x01 
#define FILE_ATTRIBUTE_HIDDEN        0x02
#define FILE_ATTRIBUTE_SYSTEM        0x04
#define FILE_ATTRIBUTE_VOLUME_LABEL  0x08
#define FILE_ATTRIBUTE_DIRECTORY     0x10
#define FILE_ATTRIBUTE_ARCHIVE       0x20
#define FILE_ATTRIBUTE_UNUSED1       0x40
#define FILE_ATTRIBUTE_UNUSED2       0x80

//
// FAT16 directory entry
//

// Structure of the Directory Entries 

// Offset   Size      Description
// 00h      8 bytes   Filename
// 08h      3 bytes   Filename Extension
// 0Bh      1 bytes   Attribute Byte
// 0Ch      1 bytes   Reserved for Windows NT
// 0Dh      1 bytes   Creation - Millisecond stamp (actual 100th of a second)
// 0Eh      2 bytes   Creation Time
// 10h      2 bytes   Creation Date
// 12h      2 bytes   Last Access Date
// 14h      2 bytes   Reserved for FAT32
// 16h      2 bytes   Last Write Time
// 18h      2 bytes   Last Write Date
// 1Ah      2 bytes   Starting cluster
// 1Ch      4 bytes   File size in bytes

// SFN Entry
struct fat16_directory_entry_d 
{
    unsigned char   FileName[11];       //8.3   

    unsigned char   Attributes;  
    unsigned char   Reserved1; 
    unsigned char   CreationMS;

    unsigned short  CreationTime; 
    unsigned short  CreationDate; 
    unsigned short  LastAccessDate;
    unsigned short  Reserved2;          //for fat32 
    unsigned short  LastWriteTime;  
    unsigned short  LastWriteDate;  
    unsigned short  StartingCluster; 

    unsigned int   FileSize; 
};  

// 
// == prototypes ==========================================
//

void 
from_FAT_name (
    char *src, 
    char *dst );

void 
to_FAT_name (
    char *src,
    char *dst );


#endif    


















