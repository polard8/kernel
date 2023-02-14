
// graphics.c

#include <kernel.h>  


// Device hotspot.
static unsigned long HotSpotX=0;
static unsigned long HotSpotY=0;

static int EnableKGWS = TRUE;

int kgws_status;
pid_t kgws_ws_PID;
int kgws_ws_status;


//see: ws.h
struct ws_info_d  WindowServerInfo;

//=================================


// called by x86_64/x64init.c
// #todo
// Maybe we can use some parametes here.

int KGWS_initialize(void)
{
    grInit();
    init_logon_manager();
    return 0;
}



// write_in_tty:
// Colocamos na tty PS2KeyboardDeviceTTY ou imprimimos na tela.

int 
write_in_tty ( 
    struct tty_d *target_tty,
    struct window_d *window, 
    int message,
    unsigned long ascii_code,
    unsigned long raw_byte )
{

//
// tty
//

    //struct tty_d *tty;
    //tty = (struct tty_d *) PS2KeyboardDeviceTTY;
    //tty = (struct tty_d *) target_tty;

//
// Event block
//

    //==============
    // [event block]
    struct window_d  *Event_Window;            //arg1 - window pointer
    int               Event_Message       =0;  //arg2 - message number
    unsigned long     Event_LongASCIICode =0;  //arg3 - ascii code
    unsigned long     Event_LongRawByte   =0;  //arg4 - raw byte
    //===================

// setup event block
// get parameters.

    Event_Window        = (struct window_d  *) window;
    Event_Message       = message;
    Event_LongASCIICode = ascii_code;
    Event_LongRawByte   = raw_byte;


    // ===========================

    // #todo
    // Send the message to the TYY,
    // this way the foreground process is able to read it
    // using stdin.
    // See:
    // devmgr.h ps2kbd.c
    // ...
    
    // only one standard event
    unsigned long event_buffer[5];


    int i=0;    //iterator.
    char bugBuffer[4];


//
// SETUP INPUT MODE
//

    // The event mode is not the mode we want.
    // We want the tty mode to put the chars into the keyboard tty.

    //if ( current_input_mode != INPUT_MODE_TTY )
    //if ( IOControl.useTTY != TRUE )
    //{
       // panic("sendto_tty: [ERROR] Wrong input mode\n");
    //}

//
// TTY INPUT MODE
//

    //if ( current_input_mode == INPUT_MODE_TTY )
    //if ( IOControl.useTTY == TRUE )
    //{

        //if ( (void *) tty != NULL )
        //{
            // ok. This is a valid tty pointer.
       
        // #test
        // Let's write something ...
            event_buffer[0] = (unsigned long) Event_Window;                      // window pointer 
            event_buffer[1] = (unsigned long) Event_Message;                     // message number.
            event_buffer[2] = (unsigned long) Event_LongASCIICode & 0x000000ff;  // ascii code
            event_buffer[3] = (unsigned long) Event_LongRawByte   & 0x000000ff;  // raw byte
       
        // #todo
        // >> PS2KeyboardDeviceTTY->_rbuffer
        // No buffer 'bruto' colocamos os raw bytes.
        // >> PS2KeyboardDeviceTTY->_cbuffer
        // No buffer 'canonico' colocamos os ascii codes.
        // ps: nao usaremos o buffer de output no caso do teclado. 
        
        //devemos cheacar se o tty esta configurado para
        //escrever na fila bruta ou canonica e escrevermos no lugar certo
        //Do mesmo modo deve ser a leitura.
        //a configuraçao pode ser feita em ring3// see:ioctl
        // esse tipo de decisao deve ficar dentro das rotinas de leitura e escrita e nao aqui.
        
        //quanto a fila eh canonica, escrevemos somente os keydown.
                
            //xxxbug[0] = 'x';  //fake bytes
            bugBuffer[0] = Event_LongASCIICode & 0x000000ff;

        // ?? #bugbug
        // Explique melhor isso. ... estamos escrevendo um byte 
        // no arquivo '0' ???
        if ( Event_Message == MSG_KEYDOWN)
            sys_write(0,bugBuffer,1);
        
        // coloca o raw byte no buffer de raw byte.
        //file_write_buffer ( PS2KeyboardDeviceTTY->_rbuffer, "dirty", 5);
        
            //
            // Suspenso.
            //
            
            //canonica
            //if ( Event_Message == MSG_KEYDOWN)
            //file_write_buffer ( tty->_cbuffer, bugBuffer , 1);
        
        
        
        // #bugbug
        // Estamos colocando um evento no buffer 'bruto'.
       
        // it is gonna write in the base of the buffer.
        // >> Essa rotina escreve na fila bruta. (raw buffer).
        // See: tty.c
        
        //__tty_write ( 
        //    (struct tty_d *) PS2KeyboardDeviceTTY, 
        //    (char *) event_buffer, 
        //    (int) (4*4) );  //16 bytes = apenas um evento.
         
         // Sinalizamos que temos um novo evento.
         
         // #todo
         // Precisamos de uma flag que diga que é para imprimirmos na tela.
         
         // o teclado esta escrevendo na tty
         // ela decide se faz echo no console ou nao,
         // dependendo da configuraçao da tty.
         // #test: fazendo echo
           // if ( (Event_Message == MSG_KEYDOWN) && ((char)bugBuffer[0] != '\n') )
           // {
                // ainda nao pode ler.
                //tty->new_event = FALSE;
         
                //console_write ( 
                    //(int) fg_console, 
                    //(const void *) bugBuffer, 
                    //(size_t) 1 );

                
                // #bugbug:
                // Usado somente para teste.
                //refresh_screen(); 
            //}
            //pode ler
           // if ( (Event_Message == MSG_KEYDOWN) && ((char)bugBuffer[0] == 'q') )
           // {
               // tty->new_event = TRUE;

             // da proxima vez escreveremos no inicio do buffer.
             //PS2KeyboardDeviceTTY->_rbuffer->_w = 0;
             // PS2KeyboardDeviceTTY->_rbuffer->_r = 0;
             //PS2KeyboardDeviceTTY->_rbuffer->_p = PS2KeyboardDeviceTTY->_rbuffer->_base; 
             //PS2KeyboardDeviceTTY->_rbuffer->_cnt = PS2KeyboardDeviceTTY->_rbuffer->_lbfsize;
             //for( xxxi=0; xxxi<BUFSIZ; xxxi++){ PS2KeyboardDeviceTTY->_rbuffer->_p[xxxi] = 0; };
           // }
  
        //}
        
        // ok
        return 0;
    //} //fim do current input mode. (TTY MODE)


fail:

    // Invalid input mode.
    debug_print ("sendto_tty: [FAIL] Invalid input mode\n");

    // fail
    return -1;
}


// ==================================
// postto_eventqueue:
// keyboard events.
// Envia eventos para a fila na thread em foreground.
// Chama um diálogo local para algumas combinações de teclas.

// Called by UserInput_SendKeyboardMessage in this document.


// #deprecated?
int 
postto_eventqueue ( 
    int tid,
    struct window_d *window, 
    int message,
    unsigned long ascii_code,
    unsigned long raw_byte )
{
    return -1;
}
//==========================================================





// ==========================================================

void kgws_enable(void)
{
    debug_print("kgws_enable: Enable KGWS\n");
         printf("kgws_enable: Enable KGWS\n");
    refresh_screen();
    
    // Sending event messages to the thread associated with the wwf.
    //current_input_mode = INPUT_MODE_SETUP;
    IOControl.useEventQueue = TRUE;
    
    EnableKGWS = TRUE;
}


void kgws_disable(void)
{
    debug_print("kgws_disable: Disable KGWS\n");
         printf("kgws_disable: Disable KGWS\n");

    backgroundDraw(COLOR_RED);

    refresh_screen();
        
    // Using unix-like TTY mode for input.
    // using the stdin.
    // current_input_mode = INPUT_MODE_TTY;
    
    // #bugbug: This is a test yet.
    //IOControl.useEventQueue = FALSE;
    
    EnableKGWS = FALSE;
}


// Fibonacci Series using Recursion 
int fib (int n)
{ 
    register int Copy = n;
    int a=0;
    int b=0;

    if (Copy <= 1){ return Copy; }
    
    a = fib(Copy - 1); 
    b = fib(Copy - 2);

    return (int) (a+b);
} 


/*
 ******************************* 
 * grPlot0:
 *      plot pixel.
 *      Low level routine.
 *      Plot into a normalized screen. kinda.
 *      #new: Plotting into a clipping window.
 */

// low level plot.
// History:
//     2020 - Created by Fred Nora.

// window ?
// Essa rotina pode pintar em qualquer posição 
// da tela do dispositivo. 
// Com origem no centro da tela.

// Aceitamos valores negativos e positivos.
// O limite máximo será modular.

// 3D fullscreen, origin in center.

int 
grPlot0 ( 
    struct window_d *clipping_window,   
    int z, 
    int x, 
    int y, 
    unsigned int color )
{

// #todo
// We can use a 'clipping window' and draw only inside this window.
// If the clipping window is NULL, so we need to use the root window.

    // #todo
    // This is a work in progress

    // Draw flag.
    int Draw = TRUE;
    int UseClipping = FALSE;
    int UsingDepthBuffer = FALSE;
    int UsingAlphaBlending = FALSE;
// left hand orientation
// z+ on top/right corner.
    int FixOrientation = TRUE;

// #todo
// We need a z-buffer or (depth buffer)
// it is used to depth testing.
// it discards some unnecessary covered plots. 
// Normalized Device Coordinates (NDC)
// We are using or own ndc style.
// Maybe it is different for diferent systens.
//      +y  +z
// -x   +   +x
// -z   -y
// We use:
// Left-hand System (LHS) 
// LHS is clockwise (CW).
// Same as Microsoft Direct3D.
// See: https://en.wikipedia.org/wiki/Direct3D
// Another way is:
// Right-Hand Coordinate System (RHS).
// RHS is counter-clockwise (CCW).

    unsigned long zBaseX=0;
    unsigned long zBaseY=0;

// #bugbug
// Precisa ser 'int', nao podemos enviar 
// valores negativos para putpixel.
     int X=0;
     int Y=0;


//
// The clipping window.
//

    //struct gws_window_d *w;

    // #todo
    // If the clipping window is invalid, 
    // so we're gonna use the root window.
    // #todo:
    // Maybe we need to use the device context structure,
    // or something like that.
    
    UseClipping = FALSE;
    
    
    /*
    if ( (void*) clipping_window != NULL )
    {
        if ( clipping_window->used  == TRUE && 
             clipping_window->magic == 1234 )
        {
            UseClipping = TRUE;
            w = (struct gws_window_d *) clipping_window;
        }
    }
    */

// #todo
// Precisamos checar algumas globais, como HotSpotX e HotSpotY.

// Usaremos a janela chamada screen se nenhuma outra foi indicada.
    //gui->screen

    // z negativo
    //  _
    //   |

    if (z < 0)
    {
        // z é módulo para todos os casos em que z é menor que 0.
        z = abs(z);

        // positivo, para direita.
        // Desloca a base x para esquerda, onde fica o z negativo
        if (x >= 0 )
        {
            X = (unsigned long) ( (unsigned long)HotSpotX  + (unsigned long)x);
        }

        // negativo, para esquerda.
        // Desloca a base x para esquerda, onde fica o z negativo
        if (x < 0 )
        {
            x = abs(x); 
            X = (unsigned long) (  (unsigned long)HotSpotX - (unsigned long)x );
        }

        // positivo, para cima.
        // Desloca a base y para baixo, onde fica o z negativo
        if ( y >= 0 )
        {
            Y = (unsigned long) ( (unsigned long)HotSpotY - (unsigned long)y );
        }

        // negativo, para baixo
        // Desloca a base y para baixo, onde fica o z negativo
        if ( y < 0 )
        {
            y = abs(y);
            Y = (unsigned long) ( (unsigned long) HotSpotY + (unsigned long) y );
        }

        if (FixOrientation == TRUE){
            X = ( (unsigned long) X - (unsigned long) z );
            Y = ( (unsigned long) Y + (unsigned long) z );
        }
        
        //if (Draw == FALSE){ return -1; }
        goto draw;
    }


    // z maior ou igual a zero.
    //    |
    //    ----
    //
    if (z >= 0)
    {
        // z é positivo para todos os casos onde z é maior igual a 0.
        
        // positivo, para direita.
        // Desloca a base x para direita, onde fica o z positivo
        if (x >= 0 )
        {
            X = (unsigned long) ( (unsigned long) HotSpotX + (unsigned long) x );
        }
        
        // negativo, para esquerda.
        // Desloca a base x para direita, onde fica o z positivo
        if (x < 0 )
        {
            x = abs(x);   
            X = (unsigned long) ( (unsigned long)HotSpotX - (unsigned long)x  );
        }

        // positivo, para cima.
        // Desloca a base y para cima, onde fica o z positivo
        if ( y >= 0 )
        {
            Y = (unsigned long) ( (unsigned long)HotSpotY - (unsigned long)y );
        }

        // negativo, para baixo
        // Desloca a base y para cima, onde fica o z positivo
        if ( y < 0 )
        {
            y = abs(y);
            Y = (unsigned long) ( (unsigned long)HotSpotY + (unsigned long)y );
        }

        if (FixOrientation == TRUE){
            X = ( (unsigned long) X + (unsigned long) z );
            Y = ( (unsigned long) Y - (unsigned long) z );
        }
        
        //if (Draw == FALSE){ return -1; }
        goto draw;
    }

    // Fail

    Draw = FALSE;

    return (-1);

//
// Draw
//

draw:
    
    //
    // Clipping
    //
    
    // #todo: 
    // We need to check the window limits
    // if we are drawing inside a given window.

    // Checking the device screen limits.
    // #todo: use a display device structure
    if ( 0 <= X < gSavedX && 0 <= Y < gSavedY )
    {
        if (Draw == TRUE)
        {
            // #bugbug
            // Já fizemos isso logo acima.
            
            if (X<0){ return -1; }
            if (Y<0){ return -1; }
            
            if ( UsingAlphaBlending == TRUE )
            {
                // #todo
                // Get the color and modify it.
                
                //color = get??()
            }
            
            // Se NÃO temos uma janela válida.
            if ( UseClipping == FALSE ){
                // device screen
                // 2D, No clipping or transformation.
                //pixelBackBufferPutpixel ( color, X, Y ); 
                backbuffer_putpixel(color,X,Y,0);
            }

             /*
            // Se temos uma janela válida.
            if ( UseClipping == TRUE ){
                if ( X >= w->left  &&
                     X <= w->right &&
                     Y >= w->top   &&
                     Y <= w->bottom )
                 {
                     pixelBackBufferPutpixel(color,X,Y); 
                 }
            }
            */
            
            // #todo
            // This is a work in progress
            
            //if( UsingDepthBuffer == TRUE )
            //{
            //    depth_buffer[ offset ] = Z;
            //}
            
            return 0;
        }
        return -1;
    }

// Fail 

    return (-1);
}

/*
 * plotLine3d: 
 */
// Bresenham in 3D
// The algorithm could be extended to three (or more) dimensions.

void 
plotLine3d (
    int x0, int y0, int z0, 
    int x1, int y1, int z1, 
    unsigned int color )
{
    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
    int dz = abs(z1-z0), sz = z0<z1 ? 1 : -1; 

    //#bugbug: This macro is wrong?!
    //int dm = grMAX3 (dx,dy,dz), i = dm; /* maximum difference */

    int dm = grMAX3(dx,dy,dz);
    register int i = dm;

    // x1 = y1 = z1 = dm/2; /* error offset */
 
    x1 = (dm >> 1);
    y1 = x1;
    z1 = x1;

    for (;;) {

        grPlot0 ( NULL, z0, x0, y0, color );
     
        if (i-- == 0) { break; }
        x1 -= dx; if (x1 < 0) { x1 += dm; x0 += sx; }
        y1 -= dy; if (y1 < 0) { y1 += dm; y0 += sy; }
        z1 -= dz; if (z1 < 0) { z1 += dm; z0 += sz; }
    };
}

// The upper-left corner and lower-right corner. 
void
rectangleZ (
    int left, int top, 
    int right, int bottom,
    unsigned int color,
    int z )
{
    // #todo
    // Check validation
    // if (left<0 ...
    
    // cima
    plotLine3d ( left, top,  z, right, top, z, color );
    // baixo
    plotLine3d ( left, bottom, z, right,bottom, z, color );
    // esquerda
    plotLine3d ( left, top, z, left, bottom, z, color );
    // direita
    plotLine3d ( right,  top, z, right, bottom, z, color );
}


// ?? what means 'm' ???
void 
plotCircleZ ( 
    int xm, 
    int ym, 
    int r, 
    unsigned int color, 
    int z )
{

    /* II. Quadrant */ 
   //int x = -r, y = 0, err = 2-2*r; 
   
    //loop
    register int x = -r;
   
    int y = 0;
    int err =  (2-(2*r));

    do {
      
      //setPixel(xm-x, ym+y); /*   I. Quadrant */
      //setPixel(xm-y, ym-x); /*  II. Quadrant */
      //setPixel(xm+x, ym-y); /* III. Quadrant */
      //setPixel(xm+y, ym+x); /*  IV. Quadrant */
      
      grPlot0 ( NULL, z, xm-x, ym+y, color);
      grPlot0 ( NULL, z, xm-y, ym-x, color);
      grPlot0 ( NULL, z, xm+x, ym-y, color);
      grPlot0 ( NULL, z, xm+y, ym+x, color);

      r = err;
      
      // #ugly routine.
      
      /* e_xy+e_y < 0 */
      if (r <= y) 
      { 
           err += ++y * 2 + 1; 
      }           
      
      /* e_xy+e_x > 0 or no 2nd y-step */
      if (r > x || err > y) 
      { 
          err += ++x * 2+1; 
      }
      
    } while (x < 0);
}


/*
 ********************************************************
 * noraDrawingStuff3: 
 *    Lot of dots in the right place. (prime stuff)
 *    2020 - Created by Fred Nora. 
 */

void noraDrawingStuff3 (int x, int y, int z)
{
    register int _x=0;
    register int _y=0;
    register int _z = z;

    int limitX = (gSavedX >> 1);
    int limitY = (gSavedY >> 1);

    // colunas.
    for (_x=x; _x<limitX; _x++)    
    {
        for (_y=y; _y<limitY; _y++)
        {
            if ( _x != 0 )
            {
                if ( _y % _x == 0 ){
                    grPlot0 ( NULL, _z, _x, _y,COLOR_GREEN );
                }
            }
        };
        
        if ( _x >= limitY) { break; }
    };
}

void demoFred0(void)
{
    register int i=0;

    for (i=0; i<100; i++){
            //noraDrawingStuff3 (i,i,0);
            noraDrawingStuff3 (-i,-i,0);
            //rectangle(8,8,i,i,COLOR_BLUE);
            //rectangleZ(i,i,i+20,i+20,COLOR_BLUE,i);
            //plotCircle ( -i % 20, -i % 20, i%20, COLOR_GREEN);
            
            plotCircleZ ( -i % 20, -i % 20, i % 20, COLOR_GREEN, i % 20);  //save this
            //plotCircleZ ( -i % 20, -i % 20, i % 20, COLOR_GREEN, i % 20);   //save this
            //cool
            //plotCircleZ ( -i % fib(20), -i % fib(20), i % fib(20), COLOR_GREEN, i % fib(20) );
            //igual o de cima.
            //plotCircleZ ( -i % fib(20), -i % fib(20), i, COLOR_GREEN, i % fib(20) );
            //plotCircleZ ( -i % fib(7), -i % fib(7), i % fib(7), COLOR_GREEN, i % fib(7) );
            //plotEllipseRect ( i, i, i*5, i*5, COLOR_BLUE);
            //plotEllipseRectZ ( i%20, i%20, i, i, COLOR_BLUE,i%20);
    };
}

void demoFred1(void)
{
    register int i=0;

    for (i=0; i<100; i++){
            //noraDrawingStuff3 (i,i,0);
            noraDrawingStuff3 (-i,-i,0);
            //rectangle(8,8,i,i,COLOR_BLUE);
            //rectangleZ(i,i,i+20,i+20,COLOR_BLUE,i);
            //plotCircle ( -i % 20, -i % 20, i%20, COLOR_GREEN);
            //plotCircleZ ( -i % 20, -i % 20, i % 20, COLOR_GREEN, i % 20);  //save this
            //plotCircleZ ( -i % 20, -i % 20, i % 20, COLOR_GREEN, i % 20);   //save this
            //cool
            plotCircleZ ( -i % fib(20), -i % fib(20), i % fib(20), COLOR_GREEN, i % fib(20) );
            //igual o de cima.
            //plotCircleZ ( -i % fib(20), -i % fib(20), i, COLOR_GREEN, i % fib(20) );
            //plotCircleZ ( -i % fib(7), -i % fib(7), i % fib(7), COLOR_GREEN, i % fib(7) );
            //plotEllipseRect ( i, i, i*5, i*5, COLOR_BLUE);
            //plotEllipseRectZ ( i%20, i%20, i, i, COLOR_BLUE,i%20);
    };
}


void demo0(void)
{
    // #test 

    //grPlot0(NULL,0,10,10,COLOR_GREEN);
    //plotCircleZ ( 0, 12, 25, COLOR_GREEN, 0); 
    //plotLine3d ( 4, 3,0, 40, 2,0, COLOR_WHITE);
                        
    //noraDrawingStuff3(20,20,0);
    //demoFred0();
    //demoFred1();
                        
    //rectangleZ( 10, 10, 10+20,10+20,COLOR_BLUE,0);
                        
    //refresh_screen();
}


int grInit (void)
{
    unsigned long deviceWidth  = (unsigned long) screenGetWidth();
    unsigned long deviceHeight = (unsigned long) screenGetHeight();

    if ( deviceWidth == 0 || deviceHeight == 0 )
    {
        debug_print ("grInit: [PANIC] w h\n");
        panic       ("grInit: [PANIC] w h\n");
    }
    
    HotSpotX = (deviceWidth>>1);
    HotSpotY = (deviceHeight>>1);

    return 0;
}


// ?? Not used yet ??
// Registrar um window server.
// See: register_ws_process
int kgwsRegisterWindowServer (pid_t pid)
{
    int Status = 0;

//#todo
    //if (pid<0 || pid >= PROCESS_COUNT_MAX)
        //panic();

    // ?? Where ??
    if (kgws_status != 1){
        Status = 1;
        goto fail;
    }else{
        kgws_ws_PID = (pid_t) pid;
        kgws_ws_status = 1;
        goto done;
    };

fail:
    printf("kgwsRegisterWindowServer: fail\n");
done:
    return 0;
}

// Registrando o processo do window server.
// See: kpid.h
int register_ws_process(pid_t pid)
{
    if ( pid<0 || pid >= PROCESS_COUNT_MAX ){
        debug_print("register_ws_process: pid\n");
        return (int) -1;
    }
    if (__gpidWindowServer != 0){
        debug_print("register_ws_process: __gpidWindowServer\n");
        return (int) -1;
    }
    __gpidWindowServer = (pid_t) pid;
    return 0;
}

//
// End
//

