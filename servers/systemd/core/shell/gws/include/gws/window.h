


struct gws_rect_d
{
    unsigned long x;
	unsigned long y;
	unsigned long width;
	unsigned long height; 
		
	unsigned long left;
	unsigned long top;
	unsigned long right;
	unsigned long bottom;
		
	unsigned long bg_color;
	
	//?? ...
};


//#todo
// A estrtutura deve ficar em user mode.
// Criaremos janelas gerenciadas por esse servidor.

struct gws_window_d 
{
    //#todo
	//...
    int dummy;
	
	//...
	
	
	struct gws_window_d *next;
};



void drawDataRectangle( unsigned long x, 
                        unsigned long y, 
						unsigned long width, 
						unsigned long height, 
						unsigned long color );


//int gws_create_window( ... );



