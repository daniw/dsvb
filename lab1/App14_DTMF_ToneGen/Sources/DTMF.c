/*****************************************************************************/
/*                                                                           */
/* FILENAME                                                                  */ 
/*   DTMF.c                                                                  */                           
/*                                                                           */
/* DESCRIPTION                                                               */
/*   DTMF Generator functionality.                                           */
/*                                                                           */
/* REVISION                                                                  */
/*   Revision: 1.00                                                          */ 
/*   Author  : Richard Sikora                                                */ 
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* HISTORY                                                                   */
/*   Revision 1.00                                                           */
/*   9 April 2010. Created by Richard Sikora.                                */
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

#include "DTMF.h"
#include "sinewaves.h"

/* Specify delay times in ms. There are 8 counts per ms */ 
/* DTMF = 70 ms. Gap = 300 ms. Redial after 3000 ms     */

#define DURATION      70*8L
#define GAP           300*8L
#define REDIAL_DELAY  3000*8L

static enum {START, BUTTON, SPACE, DONE, WAIT} state = START, nextstate = START;

static int generate_DTMF(char button);


/*****************************************************************************/
/* dial_phone_number()                                                       */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* Reads phone number from string and generates the DTMF frequencies.        */
/*                                                                           */
/*                                                                           */
/* PARAMETER 1: Pointer to string holding phone number in ASCII.             */ 
/* RETURNS:     Sum of two sine waves for the corresponding DTMF frequencies.*/
/*                                                                           */
/*****************************************************************************/

int dial_phone_number(char * phonenumber)
{
 static int offset = 0;           /* Start at beginning of phone number */
 static unsigned long timer; 
 static int button;
 int output;
 
 switch ( state)
  {
   case START: offset = 0;
               timer = 0;
               button = phonenumber[offset]; /* Read in button from phonenumber */
               if ( button != '\0' )
                 {
                   nextstate = BUTTON; /* Could use isascii() but not isalnum() here */
                 }
               else
                 {
                   nextstate = START; /* NULL string. No button information */ 
                 }   
               break;

   case BUTTON: output = generate_DTMF(button); 
               timer++;
               if ( timer >= DURATION )
                 {
                   nextstate = SPACE;
                   timer = 0;
                 }          
               else 
                 {
                   nextstate = BUTTON;
                 }   
               break;

   case SPACE: output = 0;
               timer++;
               if ( timer >= GAP)
                 {
                   timer = 0; 
                   nextstate = DONE;  
                 }  
               else
                 {
                   nextstate = SPACE;
                 }
               break;

   case DONE:  output = 0;
               offset++;                     /* Point to next button push in sequence */
               button = phonenumber[offset]; /* Get next button value */ 
               if ( button == '\0')
                  {
                   /* Null terminator at end of phone number has been reached */
                   timer = 0;  
                   nextstate = WAIT;                     
                  } 
               else
                  {
                   /* More button presses to be processed */ 
                   nextstate = BUTTON;
                  }     
	       break;

   case WAIT:  output = 0;
               timer++;
               if (timer >= REDIAL_DELAY)
                 {
                   nextstate = START; /* Redial delay has expired. Redial now */
                 }
               else 
                 {
                   nextstate = WAIT;
                 } 
               break;
   
   default:    output = 0;
               nextstate = START;
               break; 		

  }

 state = nextstate;

 return (output); 
}



/*****************************************************************************/
/* generate_DTMF()                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* Generates two sinewaves based on DTMF frequency from keypad button press. */
/*                                                                           */
/*                                                                           */
/* PARAMETER 1: The button pressed as an ASCII char e.g. '1'.                */ 
/* RETURNS:     Sum of two sine waves for the corresponding DTMF frequencies.*/
/*                                                                           */
/*****************************************************************************/


static int generate_DTMF(char button)
{
 int output;
 int temp;
 int frequency1 = 0; 
 int frequency2 = 0; 

 /* Determine the DTMF frequencies from the rows and columns. */

 switch ( button)
  {
   case '1': frequency1 = R0;  /* Row 0 Column 0 on telephone keypad */
             frequency2 = C0;
             break;

   case '2': frequency1 = R0;  /* Row 0 Column 1 on telephone keypad */
             frequency2 = C1;
	     break;
   
   case '3': frequency1 = R0;
             frequency2 = C2;
             break;

   case '4': frequency1 = R1;
             frequency2 = C0;
	     break;

   case '5': frequency1 = R1;
             frequency2 = C1;
             break;

   case '6': frequency1 = R1;
             frequency2 = C2;
	     break;

   case '7': frequency1 = R2;
             frequency2 = C0;
	     break;

   case '8': frequency1 = R2;
             frequency2 = C1;
             break;

   case '9': frequency1 = R2;
             frequency2 = C2;
             break;

   case '*': frequency1 = R3;
             frequency2 = C0;
             break;

   case '0': frequency1 = R3;
             frequency2 = C1;
             break;

   case '#': frequency1 = R3;
             frequency2 = C2;
	         break;  
	     
   default:  frequency1 = 0; /* Button not recognised. Default to no frequency */
             frequency2 = 0;
             break;
  } 


 output = 0 ; /* Default to zero output i.e. no frequency */

 if ( frequency1 > 0)
   {
     /* Generate the first frequency tone with amplitude 0.25 */
     output = generate_sinewave_1 (frequency1, 8096);
   }

 if ( frequency2 > 0)
   {
     /* Generate the second frequency tone with amplitude 0.25 */
     temp = generate_sinewave_2 (frequency2, 8096);
     output += temp; 
   }

 return (output);

}


/*****************************************************************************/
/* End of DTMF.c                                                             */
/*****************************************************************************/
