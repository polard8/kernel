
// #todo
// Aprendendo sobre gerenciamento de frames.


//#todo: tem que alocar memória para as referẽncias e par o bitmap.

//contador de referências.
//ponteiro par auma área de 4MB
//size = 0x400000
unsigned long *references;

//bitmap para controlar se os frames estão livres ou não.
//size = 0x80000 bytes 
// = 0x80000/4 longs
unsigned long *frames_bitmap;

int get_pageframe_index ( unsigned long pa ){
	
	if (pa == 0){
		return 0;
		
	}else if ( ( pa % PAGE_SIZE) != 0 ) {
	
		//o endereço menos o resto.
		//aredondando.
	    pa = pa - ( pa % PAGE_SIZE)
	};
	    
    return (int) (pa / PAGE_SIZE );
}


unsigned long get_pagereference ( unsigned long pa ){

	int i = 0;
	
    i = get_pageframe_index (va);
	
	return (unsigned long) references[i];
}


void reference_page ( unsigned long pa ){
	
	int i = 0;
	
    i = get_pageframe_index (va);
	
	unsigned long tmp = references[i];
	
	tmp++;
	references[i] = tmp;
}

void dereference_page ( unsigned long pa ){
	
	int i = 0;
	
    i = get_pageframe_index (va);
	
	unsigned long tmp = references[i];
	
	if ( tmp == 1 )
	{
	    tmp--;
	    references[i] = tmp;
		//#todo liberar a página.
	
	}else if ( tmp != 0 ){

	    tmp--;
	    references[i] = tmp;	
	}
}

void invalidate_reference ( unsigned long pa ){
	
	int i = 0;
	
    i = get_pageframe_index (va);
	
	references[i] = 0;
}



//
// ====================================
//

// Credits:
// http://shell-storm.org/blog/Physical-page-frame-allocation-with-bitmap-algorithms/
// by Jonathan Salwan 


/* 32 bytes = 256 pages monitoring */
//static char pageBitMap[32];


//ponteiro para uma área de memória onde ficarão os bitmaps.
//usando variáveis de 32bit;
unsigned long *pageBitMap;


int pageBitMapSize = (0x80000/4);


/* Return 0 to FREE, otherwise 1 to USED */
int getPageStatus(int pageNumber)
{
  if (pageNumber < 32)
    return ((pageBitMap[0] >> pageNumber) & 1);
  return ((pageBitMap[pageNumber/32] >> pageNumber % 32) & 1);
}


/*
** Return page number and set USED flag,
** if FREE page isn't available, -1 is returned
*/
int getFreePage(void)
{
  int i, x;

  for (i = 0; i < pageBitMapSize ; i++)
    for (x = 0 ; x < 32 ; x++)
      if (!((pageBitMap[i] >> x) & 1))
        return ((i * 32) + x);
  return -1;
}


/* Set USED flag on pageNumber, -1 is returned if page is already USED */
int setPageIsUsed(int pageNumber)
{
  if (getPageStatus(pageNumber))
    return -1;
  pageBitMap[pageNumber/32] |= 1 << (pageNumber % 32);
  return 0;
}


/* Set FREE flag on pageNumber, -1 is returned if page is already FREE */
int setPageIsFree(int pageNumber)
{
  if (!getPageStatus(pageNumber))
    return -1;
  pageBitMap[pageNumber/32] &= ~(1 << (pageNumber % 32));
  return 0;
}


/* Return number of pages which is Used */
int howManyPagesIsUsed(void)
{
  int i, x, cpt = 0;

  for (i = 0; i < pageBitMapSize ; i++)
    for (x = 0 ; x < 32 ; x++)
      cpt += (pageBitMap[i] >> x) & 1;
  return cpt;
}


/* Return number of pages which is Free */
int howManyPagesIsFree(void)
{
  int i, x, cpt = 0;

  for (i = 0; i < pageBitMapSize ; i++)
    for (x = 0 ; x < 32 ; x++)
      cpt += !((pageBitMap[i] >> x) & 1);
  return cpt;
}





