
// x64gdt.h

#ifndef ____X64GDT_H
#define ____X64GDT_H    1


//#bugbug
//sei que existe um máximo, mas não sei se existe mínimo.
//#define	MINGDTSIZ	512
//#define	MAXGDTSIZ	8192 //??8191 ??? e a NULL ???
//#define MINGDTSIZ       PAGE_SIZE
//#define MAXGDTSIZ 65536
//??

//índices na gdt
#define GNULL_SEL	0	/* Null descriptor */
#define GCODE_SEL	1	/* Kernel code descriptor */
#define GDATA_SEL	2	/* Kernel data descriptor */
#define GUCODE_SEL	3	/* User code descriptor */
#define GUDATA_SEL	4	/* User data descriptor */
#define GTSS_SEL	5   //tss
#define GLDT_SEL	6   /* Default LDT descriptor */


#define SEL_KPL  0	/* kernel privilege level */
#define SEL_UPL  3	/* user privilege level */


/* system segments and gate types */
#define SDT_SYSNULL	 0	/* system null */
#define SDT_SYS286TSS	 1	/* system 286 TSS available */
#define SDT_SYSLDT	 2	/* system local descriptor table */
#define SDT_SYS286BSY	 3	/* system 286 TSS busy */
#define SDT_SYS286CGT	 4	/* system 286 call gate */
#define SDT_SYSTASKGT	 5	/* system task gate */
#define SDT_SYS286IGT	 6	/* system 286 interrupt gate */
#define SDT_SYS286TGT	 7	/* system 286 trap gate */
#define SDT_SYSNULL2	 8	/* system null again */
#define SDT_SYS386TSS	 9	/* system 386 TSS available */
#define SDT_SYSNULL3	10	/* system null again */
#define SDT_SYS386BSY	11	/* system 386 TSS busy */
#define SDT_SYS386CGT	12	/* system 386 call gate */
#define SDT_SYSNULL4	13	/* system null again */
#define SDT_SYS386IGT	14	/* system 386 interrupt gate */
#define SDT_SYS386TGT	15	/* system 386 trap gate */


/* memory segment types */
#define SDT_MEMRO	16	/* memory read only */
#define SDT_MEMROA	17	/* memory read only accessed */
#define SDT_MEMRW	18	/* memory read write */
#define SDT_MEMRWA	19	/* memory read write accessed */
#define SDT_MEMROD	20	/* memory read only expand dwn limit */
#define SDT_MEMRODA	21	/* memory read only expand dwn limit accessed */
#define SDT_MEMRWD	22	/* memory read write expand dwn limit */
#define SDT_MEMRWDA	23	/* memory read write expand dwn limit acessed */
#define SDT_MEME	24	/* memory execute only */
#define SDT_MEMEA	25	/* memory execute only accessed */
#define SDT_MEMER	26	/* memory execute read */
#define SDT_MEMERA	27	/* memory execute read accessed */
#define SDT_MEMEC	28	/* memory execute only conforming */
#define SDT_MEMEAC	29	/* memory execute only accessed conforming */
#define SDT_MEMERC	30	/* memory execute read conforming */
#define SDT_MEMERAC	31	/* memory execute read accessed conforming */



#define GSEL(s,r) (((s) << 3) | r)



/*
 * Memory and System segment descriptors
 * NetBSD style.
 * #obs: Podemos fazer listas de segmentos que formem gdts.
 */

// See:
// https://wiki.osdev.org/Global_Descriptor_Table

// gdt structure.
struct segment_descriptor_d 
{
    // LIMIT LOW
    unsigned sd_lolimit :16;  //segment extent (lsb) 

    // BASE LOW
    unsigned sd_lobase :24;  //segment base address (lsb) 

    unsigned sd_type :5;  //segment type
    unsigned sd_dpl  :2;  //segment descriptor priority level 
    unsigned sd_p    :1;  //segment descriptor present 

    // LIMIT HIGH
    unsigned sd_hilimit :4;  //segment extent (msb) 

    unsigned sd_xx    :2;  //unused 
    unsigned sd_def32 :1;  //default 32 vs 16 bit size 
    unsigned sd_gran  :1;  //limit granularity (byte/page) 

   // BASE HIGH
    unsigned sd_hibase :8;  //segment base address (msb) 

} __attribute__((packed));


// Isso é uma gdt com 32 entradas.
static struct segment_descriptor_d xxx_gdt[16];


// Isso é o registro da gdt
static struct gdt_ptr_d xxx_gdt_ptr;


// ======================



/* 
 * Special pointer which includes the limit: The max bytes
 *  taken up by the GDT, minus 1. Again, this NEEDS to be packed. 
 */

// gdtr structure pointer
struct gdt_ptr_d
{
    unsigned short limit;  // 16
    unsigned long  base;   // 64 

} __attribute__((packed));


/*
 * Gate descriptors (e.g. indirect descriptors)
 * NetBSD style.
 */

struct gate_descriptor_d {

    // OFFSET LOW
    unsigned gd_looffset :16;  //gate offset (lsb) 
    unsigned gd_selector :16;  //gate segment selector 

    unsigned gd_stkcpy :5;  //number of stack wds to cpy 
    unsigned gd_xx     :3;  //unused 
    unsigned gd_type   :5;  //segment type 
    unsigned gd_dpl    :2;  //segment descriptor priority level 
    unsigned gd_p      :1;  //segment descriptor present 

    // OFFSET HIGH
    unsigned gd_hioffset  :16;  //gate offset (msb) 

} __attribute__((packed));


/*
struct ldt_descriptor_d {
	vaddr_t ld_base;
	uint32_t ld_entries;
} __attribute__((packed));
*/


/*
 * Generic descriptor
 */

/*
union descriptor_d {

    struct segment_descriptor_d  sd;
    struct gate_descriptor_d     gd;
    struct ldt_descriptor_d      ld;
    uint32_t raw[2];
    //uint64_t raw64;
} __attribute__((packed));
*/


/*
 * region descriptors, 
 * used to load gdt/idt tables before segments yet exist.
 */

/*
struct region_descriptor_d 
{
    unsigned rd_limit :16;    // segment extent 
    unsigned rd_base  :32;    // base address  #todo: change to 64

} __attribute__((packed));
*/




//
// == prototypes ==============
//

void
setsegment ( 
    struct segment_descriptor_d *sd, 
    const void *base, 
    size_t limit,
    int type, 
    int dpl, 
    int def32, 
    int gran );


void
setsegmentNR ( 
    int number, 
    const void *base, 
    size_t limit,
    int type, 
    int dpl, 
    int def32, 
    int gran );



#endif    
























