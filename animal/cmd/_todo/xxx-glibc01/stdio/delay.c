/*
 *  ZeX/OS
 *  Copyright (C) 2007  Tomas 'ZeXx86' Jedrzejek (zexx86@gmail.com)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


/*
 * Allright, let's review how we're going to do this.
 *
 * Goal:
 * The goal is to create a reasonably accurate version of the delay()
 * function, which creates a delay in multiples of one millisecond.
 *
 * Restrictions:
 * We don't want to use the PIT for the delay.  In your average
 * bare-hardware system (ie OS) you'll be using the PIT for quite a few
 * other things already (in my OS code, channel 0 and 1 are used by the
 * scheduler, and channel 2 would probably be needed to control the
 * speaker.)
 *
 * Method:
 * A simple loop would delay the computer wonderfully.  Ie, take something
 * like:
 *
 *         for(i=0;i<BIGNUMBER;i++);  // Delay loop
 *
 * That kills time wonderfully.  All we need to do is to find out what
 * BIGNUMBER we need to use to delay one millisecond.  Finding the correct
 * BIGNUMBER for your machine is called *delay loop calibration*.
 *
 * We can calibrate the delay loop using the PIT.  In the initialisation
 * phase of the OS, when the PIT is not yet hooked to the scheduler, it
 * can be freely used to do this.  When the delay loop has been calibrated
 * against the PIT, the PIT is free to be used for other purposes.
 *
 * There are many ways to calibrate a delay loop with the PIT.  This is
 * one way (used in Linux.)  More documentation in the code.
 */

/**************************************************************************/

/*
 * The delay function:
 * Have a look at this function before you look at the calibration code.
 * Basically, delay_count is the number you have to count to in order to
 * kill 1ms.  delay() takes the amount of milliseconds to delay as
 * parameter.
 *
 * The goal of the rest of this code is to determine what delay_count *is*
 * for your machine.
 *
 * Keep delay_count initialised to 1.  We'll need that later.
 */

static unsigned long delay_count = 1;


/*
 * When I was testing the delay code, I notice that the calibration we use
 * is very delicate.  Originally, I had inlined the delay for() loops into
 * the delay() and calibrateDelayLoop() functions, but this doesn't work.
 * Due to different register allocation or something similar the compiler
 * might have generated different code in the two situations (I didn't
 * check this.)  Or alignment differences might have caused the problems.
 * Anyway, to solve the problem, we always use the __delay() function for
 * the delay for() loop, because it always is the same code with the same
 * alignment. __delay() is called from delay() as well as from
 * calibrateDelayLoop().  By using __delay() we can fine-tune our
 * calibration without it losing its finesse afterwards.
 */


void __delay (loops){
//void __delay ( unsigned long loops){	
	
    unsigned long c;
	
    for ( c=0; c<loops; c++ );
}


void delay (unsigned long milliseconds){
	
	/* Delay milliseconds ms */
    __delay ( milliseconds*delay_count );     
}


/* The end */

