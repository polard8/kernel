
#ifndef  __FAT_LFN_H
#define  __FAT_LFN_H    1


// Um arquivo pode usar ate 21 entradas.
// 256 ?
//#define MAX_LFN_CHARACTERS  260
//#define MAX_LFN_DIRENTS     20

//#define FAT_LFN_ORDINAL_FIELD    0x40
//#define FAT_LFN_TYPE_FIELD       0x0  

// #todo
// LFN Entry
struct fat16_lfn_directory_entry_d 
{
    unsigned char  ordinal_field;    // offset 0  - ordinal.
    unsigned short name1[5];         // offset 1  - name part1 (unicode)
    // unsigned char name1[10];      // 
    unsigned char  flag_byte;        // offset 11 - Flag
    unsigned char  reserved;         // offset 12 - Reserved
    unsigned char  checksum;         // offset 13 - Checksum.
    unsigned short name2[6];         // offset 14 - name part2  (unicode)
    unsigned short thing;            // offset 26 - always '0'
    unsigned short name3[2];         // offset 28 - name part3   (unicode)
};

#endif    



