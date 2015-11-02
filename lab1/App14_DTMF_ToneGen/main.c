/*****************************************************************************/
/*                                                                           */
/* PROJECT                                                                   */
/*  DTMF Generator                                                           */
/*                                                                           */
/* FILENAME                                                                  */
/*  main.c                                                                   */
/*                                                                           */
/* DESCRIPTION                                                               */
/*   TMS320C5505 USB Stick. Code containing main() function.                 */
/*                                                                           */
/* REVISION                                                                  */
/*   Revision: 1.01                                                          */
/*   Author  : Richard Sikora                                                */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* HISTORY                                                                   */
/*   Revision 1.00                                                           */
/*   9th April 2010. Created by Richard Sikora                               */
/*                                                                           */
/*   Revision 1.01                                                           */
/*   8th August 2010. Converted to use CSL.                                  */
/*                                                                           */
/*****************************************************************************/
/*
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#include "stdio.h"
#include "usbstk5505.h"
#include "aic3204.h"
#include "sinewaves.h"
#include "PLL.h"
#include "DTMF.h"

#define SAMPLES_PER_SECOND 8000

Int16 left_input;
Int16 right_input;
Int16 left_output;
Int16 right_output;

// Enter telephone number to be dialed here
char telephone_number[] = "00800800800";

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  main( )                                                                 *
 *                                                                          *
 * ------------------------------------------------------------------------ */

void main( void ) 
{
    /* Initialize BSL */
    USBSTK5505_init( );

	/* Initialize Phase Locked Loop (PLL) */
    pll_frequency_setup(100);

    /* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();
    
    /* Initialise the AIC3204 codec */
    aic3204_init(); 

    printf("\n\nRunning Project DTMF Generator\n");
    printf( "Generates DTMF frequencies for telephone number --> to Headphones/Lineout\n\n" );

   /* Setup sampling frequency */

    set_sampling_frequency_and_gain(SAMPLES_PER_SECOND, 0);
  
    asm(" bclr XF");                // Turn off XF LED
   
    while(1)
    {
     aic3204_codec_read(&left_input, &right_input); // Configured for one interrupt per two channels.
     
     left_output = right_output = dial_phone_number(&telephone_number[0]);

     if ( left_output > 0)
      {
       asm(" bset XF");
      }
     else
      {
       asm(" bclr XF");
      }
 
     aic3204_codec_write(left_output/2, right_output/2);
    }
}

/*****************************************************************************/
/* End of main.c                                                             */
/*****************************************************************************/

