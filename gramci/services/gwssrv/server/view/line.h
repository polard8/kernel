
/*
 * File: line.h
 * 
 * 
 */


// See: https://en.wikipedia.org/wiki/Line_drawing_algorithm
void
A_naive_line_drawing_algorithm(
    unsigned long x1,
    unsigned long x2, 
    unsigned long y1, 
    unsigned long y2, 
    unsigned long color );
    
void test_draw_line(void);
void test_draw_line2(void);



/* 
 * lineBackbufferDrawHorizontalLine:
 *     Draw a horizontal line on backbuffer. 
 */

void 
lineBackbufferDrawHorizontalLine ( 
    unsigned long x1,
    unsigned long y, 
    unsigned long x2,  
    unsigned long color );
    
    

//
// End.
//


