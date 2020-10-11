

   // the font support.


//U8 waves[8*4]={
static unsigned char waves[4*8] = {
0x00,0x11,0xAA,0x44,0x00,0x11,0xAA,0x44,
0x00,0x22,0x55,0x88,0x00,0x22,0x55,0x88,
0x00,0x44,0xAA,0x11,0x00,0x44,0xAA,0x11,
0x00,0x88,0x55,0x22,0x00,0x88,0x55,0x22
};


static unsigned char eye_sprite[6*8] = {

//0 -   
	0xFF, //    11111111
	0xFF, //    11111111
	0xFF, //    11111111
	0xFF, //    11111111
	0xFF, //    11111111
	0xFF, //    11111111
	0xFF, //    11111111
	0xFF, //    11111111


//1  
	0x7e, //    0111 1110
	0x81, //    1000 0001
	0xa9, //    1010 1001
	0xa9, //    1010 1001
	0xa9, //    1010 1001
	0x81, //    1000 0001
	0x81, //    1000 0001
	0x7e, //    0111 1110 

//2
	0x7e, //    0111 1110
	0x81, //    1000 0001
	0x95, //    1001 0101
	0x95, //    1001 0101
	0x95, //    1001 0101
	0x81, //    1000 0001
	0x81, //    1000 0001
	0x7e, //    0111 1110 

 
//3 
	0x7e, //    0111 1110
	0x81, //    1000 0001
	0x8b, //    1000 1011
	0x8b, //    1000 1011
	0x8b, //    1000 1011
	0x81, //    1000 0001
	0x81, //    1000 0001
	0x7e, //    0111 1110 
 
//4 
	0x7e, //    0111 1110
	0x81, //    1000 0001
	0x87, //    1000 0111
	0x87, //    1000 0111
	0x87, //    1000 0111
	0x81, //    1000 0001
	0x81, //    1000 0001
	0x7e, //    0111 1110 


// 5
// monstrinho
	0x18, //    11111111
	0x3C, //    11111111
	0x7E, //    11111111
	0xDB, //    11111111
	0xFF, //    11111111
	0x24, //    11111111
	0x5A, //    11111111
	0x81, //    11111111

};







//
// Font
//

int gfontSize;

//As fontes usadas pelo servidor gws
unsigned long gws_currentfont_address;  // fonte atual.
unsigned long g8x8fontAddress;          // 8×8, 80×25,CGA, EGA
unsigned long g8x14fontAddress;         // 8x14,80×25,EGA
unsigned long g8x16fontAddress;         // ??
unsigned long g9x14fontAddress;         // 9x14,80×25,MDA, Hercules
unsigned long g9x16fontAddress;         // 9x16,80×25,VGA


unsigned long gws_eye_sprite_address;



//
// == prototypes =============================
//

int gwssrv_init_font(void);





