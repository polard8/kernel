// * credits: NetBSD


//#bugbug
//sei que existe um máximo, mas não sei se existe mínimo.
//#define	MINGDTSIZ	512
//#define	MAXGDTSIZ	8192 //??8191 ??? e a NULL ???
//#define MINGDTSIZ       PAGE_SIZE
//#define MAXGDTSIZ 65536
//??


/*
 * Memory and System segment descriptors
 * NetBSD style.
 * #obs: Podemos fazer listas de segmentos que formem gdts.
 */

struct segment_descriptor_d {
	
	// LIMIT LOW
	unsigned sd_lolimit:16;		//segment extent (lsb) 
	
	// BASE LOW
	unsigned sd_lobase:24;		//segment base address (lsb) 
	
	unsigned sd_type:5;		    //segment type
	
	unsigned sd_dpl:2;		    //segment descriptor priority level 
	
	unsigned sd_p:1;		    //segment descriptor present 
	
	// LIMIT HIGH
	unsigned sd_hilimit:4;		//segment extent (msb) 
	
	unsigned sd_xx:2;		    //unused 
	
	unsigned sd_def32:1;		//default 32 vs 16 bit size 
	
	unsigned sd_gran:1;		    //limit granularity (byte/page) 
	
	// BASE HIGH
	unsigned sd_hibase:8;    	//segment base address (msb) 
	
} __attribute__((packed));


/* Special pointer which includes the limit: The max bytes
*  taken up by the GDT, minus 1. Again, this NEEDS to be packed */
struct gdt_ptr_d
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));



/*
 * Gate descriptors (e.g. indirect descriptors)
 * NetBSD style.
 */

struct gate_descriptor_d {
	
	// OFFSET LOW
	unsigned gd_looffset:16;	//gate offset (lsb) 
	
	unsigned gd_selector:16;	//gate segment selector 
	unsigned gd_stkcpy:5;		//number of stack wds to cpy 
	unsigned gd_xx:3;		    //unused 
	unsigned gd_type:5;		    //segment type 
	unsigned gd_dpl:2;		    //segment descriptor priority level 
	unsigned gd_p:1;		    //segment descriptor present 
	
	// OFFSET HIGH
	unsigned gd_hioffset:16;	//gate offset (msb) 
	
} __attribute__((packed));



struct ldt_descriptor_d {
	vaddr_t ld_base;
	uint32_t ld_entries;
} __attribute__((packed));



/*
 * Generic descriptor
 */


union descriptor_d {
	struct segment_descriptor_d sd;
	struct gate_descriptor_d gd;
	struct ldt_descriptor_d ld;
	uint32_t raw[2];
	//uint64_t raw64;
} __attribute__((packed));



/*
 * region descriptors, used to load gdt/idt tables before segments yet exist.
 */

struct region_descriptor_d {
	unsigned rd_limit:16;		//segment extent 
	unsigned rd_base:32;		//base address  
} __attribute__((packed));


// #todo
// Isso é uma lista de entradas, a primeira é NULL.
// Precisamos reavaliar o tamanho.

//#todo
//lembrando que cada núcleo terá sua gdt
//Então isso provavelmente está errado, porque contempla apenas um núcleo.

//#todo
//Cada estrtutura de processador vai apenatar para uama gdt.

/* 
 Our GDT, with 3 entries, and finally our special GDT pointer 
 */

// #importante
// GDT for single processor.

struct segment_descriptor_d xxx_gdt[8];
struct gdt_ptr_d xxx_gdt_ptr;






void
setgate(struct gate_descriptor_d *gd, void *func, int args, int type, int dpl,
    int sel);

void
unsetgate(struct gate_descriptor_d *gd);

void
setregion(struct region_descriptor_d *rd, void *base, size_t limit);

void
setsegment(struct segment_descriptor_d *sd, const void *base, size_t limit,
    int type, int dpl, int def32, int gran);


//
// End.
//

