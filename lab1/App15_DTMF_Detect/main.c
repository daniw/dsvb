
/*****************************************************************************/
/*                                                                           */
/* PROJECT                                                                   */
/*   Goertzel Algorithm                                                      */
/*                                                                           */
/* FILENAME                                                                  */
/*   main.c                                                                  */
/*                                                                           */
/* DESCRIPTION                                                               */
/*   TMS320C5505 USB Stick Application 15. Goertzel Algorithm.               */
/*   Using the Goertzel Algorithm to identify DTMF frequencies from keypad   */
/*   with the TMS320C5505 USB Stick.                                         */
/*                                                                           */
/* REVISION                                                                  */
/*   Revision: 1.01                                                          */
/*   Author  : Richard Sikora                                                */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* HISTORY                                                                   */
/*                                                                           */
/*   Revision 1.00                                                           */
/*   12th April 2010. Modified from TMS320C5510 DSK code.                    */
/*                                                                           */
/*   Revision 1.01.                                                          */
/*   8th August 2010. Modified to be compatible with CSL.                    */
/*                                                                           */
/*****************************************************************************/
/*
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
#include "PLL.h"
#include "stereo.h"
#include "goertzel.h"
#include "config.h"

Int16 left_input;
Int16 right_input;
Int16 mono_input;

unsigned long int i = 0;

short int goertzel_output_697_Hz;
short int goertzel_output_770_Hz;
short int goertzel_output_852_Hz;
short int goertzel_output_941_Hz;

short int goertzel_output_1209_Hz;
short int goertzel_output_1336_Hz;
short int goertzel_output_1477_Hz;
short int goertzel_output_1633_Hz;

#if FILTER_IMP_VER == 0
	short int delay_697_Hz[3] = { 0, 0, 0 };
	short int delay_770_Hz[3] = { 0, 0, 0 };
	short int delay_852_Hz[3] = { 0, 0, 0 };
	short int delay_941_Hz[3] = { 0, 0, 0 };

	short int delay_1209_Hz[3] = { 0, 0, 0 };
	short int delay_1336_Hz[3] = { 0, 0, 0 };
	short int delay_1477_Hz[3] = { 0, 0, 0 };
	short int delay_1633_Hz[3] = { 0, 0, 0 };
#else
	short int delay_697_Hz[2] = { 0, 0 };
	short int delay_770_Hz[2] = { 0, 0 };
	short int delay_852_Hz[2] = { 0, 0 };
	short int delay_941_Hz[2] = { 0, 0 };

	short int delay_1209_Hz[2] = { 0, 0 };
	short int delay_1336_Hz[2] = { 0, 0 };
	short int delay_1477_Hz[2] = { 0, 0 };
	short int delay_1633_Hz[2] = { 0, 0 };
#endif

/* Variable to build outputs of filters as a series of bits */ 
short int goertzel_bit_mask = 0;

unsigned int N = 8000;
unsigned int D = 500;

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  main( )                                                                 *
 *                                                                          *
 * ------------------------------------------------------------------------ */

void main( void ) 
{

    /* Initialize BSL */
    USBSTK5505_init( );
    
    /* Initialize the Phase Locked Loop in EEPROM */
    pll_frequency_setup(100);

    /* Initialize hardware interface and I2C for code */
    aic3204_hardware_init();
    
    /* Initialize the AIC3204 codec */
    aic3204_init(); 
 
    /* Set sampling frequency in Hz and ADC gain in dB */
    set_sampling_frequency_and_gain(SAMPLES_PER_SECOND, GAIN_IN_dB);

    printf("\nRunning Goertzel Algorithm Project\n\n");
    printf("For the filter implementation the function goertzel_filter_v%d is used !!!\n",FILTER_IMP_VER);
    printf("For power calculation the function goertzel_output_power_v%d is used !!!\n",POWER_CALC_VER);

    asm(" bclr XF");
   
    while(1)
    {
     aic3204_codec_read(&left_input, &right_input); /* Configured for one interrupt per two channels */

     mono_input = stereo_to_mono(left_input, right_input); /* Mono input from microphone */ 
 
     /* Perform Goertzel filter for each frequency. */
#if FILTER_IMP_VER == 0
     goertzel_filter_v0( &delay_697_Hz[0], mono_input, COEFFICIENT_697_Hz);
     goertzel_filter_v0( &delay_770_Hz[0], mono_input, COEFFICIENT_770_Hz);
     goertzel_filter_v0( &delay_852_Hz[0], mono_input, COEFFICIENT_852_Hz);
     goertzel_filter_v0( &delay_941_Hz[0], mono_input, COEFFICIENT_941_Hz);
     goertzel_filter_v0( &delay_1209_Hz[0], mono_input, COEFFICIENT_1209_Hz);
     goertzel_filter_v0( &delay_1336_Hz[0], mono_input, COEFFICIENT_1336_Hz);
     goertzel_filter_v0( &delay_1477_Hz[0], mono_input, COEFFICIENT_1477_Hz);
     // detection of keys in fourth column not implemented
     //goertzel_filter_v0( &delay_1633_Hz[0], mono_input, COEFFICIENT_1633_Hz);
#else
     goertzel_filter_v1( &delay_697_Hz[0], mono_input, COEFFICIENT_697_Hz);
     goertzel_filter_v1( &delay_770_Hz[0], mono_input, COEFFICIENT_770_Hz);
     goertzel_filter_v1( &delay_852_Hz[0], mono_input, COEFFICIENT_852_Hz);
     goertzel_filter_v1( &delay_941_Hz[0], mono_input, COEFFICIENT_941_Hz);
     goertzel_filter_v1( &delay_1209_Hz[0], mono_input, COEFFICIENT_1209_Hz);
     goertzel_filter_v1( &delay_1336_Hz[0], mono_input, COEFFICIENT_1336_Hz);
     goertzel_filter_v1( &delay_1477_Hz[0], mono_input, COEFFICIENT_1477_Hz);
     // detection of keys in fourth column not implemented
     //goertzel_filter_v1( &delay_1633_Hz[0], mono_input, COEFFICIENT_1633_Hz);
#endif
               
     N++;

     /* Following processes are all staggered by one to save execution time */
     if (D+0 == N)
       { 
#if POWER_CALC_VER == 0
    		 goertzel_output_697_Hz = goertzel_output_power_v0( &delay_697_Hz[0], COEFFICIENT_697_Hz);
#else
    		 goertzel_output_697_Hz = goertzel_output_power_v1( &delay_697_Hz[0],b_RE_697_Hz,b_IM_697_Hz);
#endif
        if ( goertzel_output_697_Hz > GOERTZEL_THRESHOLD)
         {
          goertzel_bit_mask |= 0x0001; /* Set bit 0 in bit mask */
         }
        else
         {
          goertzel_bit_mask &= 0xFFFE; /* Clear bit 0 in bit mask */
         }
       }  
     else if (D+1 == N)
       { 
#if POWER_CALC_VER == 0
    		 goertzel_output_770_Hz = goertzel_output_power_v0( &delay_770_Hz[0],COEFFICIENT_770_Hz);
#else
    		 goertzel_output_770_Hz = goertzel_output_power_v1( &delay_770_Hz[0],b_RE_770_Hz,b_IM_770_Hz);
#endif
        if ( goertzel_output_770_Hz > GOERTZEL_THRESHOLD)
         {
          goertzel_bit_mask |= 0x0002; /* Set bit 1 in bit mask */
         }
        else
         {
          goertzel_bit_mask &= 0xFFFD; /* Clear bit 1 in bit mask */
         }
       }
     else if (D+2 == N)
       { 
#if POWER_CALC_VER == 0
    		 goertzel_output_852_Hz = goertzel_output_power_v0( &delay_852_Hz[0],COEFFICIENT_852_Hz);
#else
    		 goertzel_output_852_Hz = goertzel_output_power_v1( &delay_852_Hz[0],b_RE_852_Hz,b_IM_852_Hz);
#endif
        if ( goertzel_output_852_Hz > GOERTZEL_THRESHOLD)
          {
           goertzel_bit_mask |= 0x0004; /* Set bit 2 in bit mask */
          }
        else
         {
          goertzel_bit_mask &= 0xFFFB; /* Clear bit 2 in bit mask */
         }                                                                      
       }  
     else if (D+3 == N)
       { 
#if POWER_CALC_VER == 0
    		 goertzel_output_941_Hz = goertzel_output_power_v0( &delay_941_Hz[0], COEFFICIENT_941_Hz);
#else
    		 goertzel_output_941_Hz = goertzel_output_power_v1( &delay_941_Hz[0],b_RE_941_Hz,b_IM_941_Hz);
#endif
        if ( goertzel_output_941_Hz > GOERTZEL_THRESHOLD)
         {
          goertzel_bit_mask |= 0x0008; /* Set bit 3 in bit mask */
         }
        else
         {
          goertzel_bit_mask &= 0xFFF7; /* Clear bit 3 in bit mask */
         } 
       }
     else if (D+4 == N)
       { 
#if POWER_CALC_VER == 0
    		 goertzel_output_1209_Hz = goertzel_output_power_v0( &delay_1209_Hz[0], COEFFICIENT_1209_Hz);
#else
    		 goertzel_output_1209_Hz = goertzel_output_power_v1( &delay_1209_Hz[0],b_RE_1209_Hz,b_IM_1209_Hz);
#endif
        if ( goertzel_output_1209_Hz > GOERTZEL_THRESHOLD)
          {
           goertzel_bit_mask |= 0x0010; /* Set bit 4 in bit mask */
          }
        else
          {
           goertzel_bit_mask &= 0xFFEF; /* Clear bit 4 in bit mask */
          } 
       }  
     else if (D+5 == N)
       { 
#if POWER_CALC_VER == 0
    		 goertzel_output_1336_Hz = goertzel_output_power_v0( &delay_1336_Hz[0], COEFFICIENT_1336_Hz);
#else
    		 goertzel_output_1336_Hz = goertzel_output_power_v1( &delay_1336_Hz[0],b_RE_1336_Hz,b_IM_1336_Hz);
#endif
        if ( goertzel_output_1336_Hz > GOERTZEL_THRESHOLD)
          {
           goertzel_bit_mask |= 0x0020; /* Set bit 5 in bit mask */
          }
        else
          {
           goertzel_bit_mask &= 0xFFDF; /* Clear bit 5 in bit mask */
          } 
       }
     else if (D+6 == N)
       { 
#if POWER_CALC_VER == 0
    		 goertzel_output_1477_Hz = goertzel_output_power_v0( &delay_1477_Hz[0], COEFFICIENT_1477_Hz);
#else
    		 goertzel_output_1477_Hz = goertzel_output_power_v1( &delay_1477_Hz[0],b_RE_1477_Hz,b_IM_1477_Hz);
#endif
        if ( goertzel_output_1477_Hz > GOERTZEL_THRESHOLD)
          {
           goertzel_bit_mask |= 0x0040; /* Set bit 6 in bit mask */
          }
        else
          {
           goertzel_bit_mask &= 0xFFBF; /* Clear bit 6 in bit mask */
          } 
       }  
     else if (D+7 == N)
       {
#if POWER_CALC_VER == 0
    		 goertzel_output_1633_Hz = goertzel_output_power_v0( &delay_1633_Hz[0], COEFFICIENT_1633_Hz);
#else
    		 goertzel_output_1633_Hz = goertzel_output_power_v1( &delay_1633_Hz[0],b_RE_1633_Hz,b_IM_1633_Hz);
#endif
        if ( goertzel_output_1633_Hz > GOERTZEL_THRESHOLD)
          {
           goertzel_bit_mask |= 0x0080; /* Set bit 7 in bit mask */
          }
        else
          {
           goertzel_bit_mask &= 0xFF7F; /* Clear bit 7 in bit mask */
          }
        }
     else if (D+8 == N)
        {
    	 // For debugging only (requires a lot of computing power, use with care)
    	 // Print calculated power for the different frequencies
    	 // printf("697Hz       770Hz       852Hz       941Hz       1209Hz      1336Hz      1477Hz      1633Hz\n");
    	 // printf("%-10i, %-10i, %-10i, %-10i, %-10i, %-10i, %-10i, %-10i\n",	goertzel_output_697_Hz, goertzel_output_770_Hz,
    	 //     																goertzel_output_852_Hz, goertzel_output_941_Hz,
    	 //         															goertzel_output_1209_Hz, goertzel_output_1336_Hz,
    	 //         															goertzel_output_1477_Hz, goertzel_output_1633_Hz);

    	 /* Display button pressed on Stdout then clear bit mask */
    	 if ( BUTTON_0 == goertzel_bit_mask)
          {
    		 puts("Button 0 pressed.\n");
          }
    	 else if ( BUTTON_1 == goertzel_bit_mask)
    	  {
    	     puts ("Button 1 pressed.\n");
    	  }
    	 else if ( BUTTON_2 == goertzel_bit_mask)
    	  {
    	    puts ("Button 2 pressed.\n");
    	  }
    	 else if ( BUTTON_3 == goertzel_bit_mask)
    	  {
    	    puts("Button 3 pressed.\n");
    	  }
    	 else if ( BUTTON_4 == goertzel_bit_mask)
    	  {
    	     puts ("Button 4 pressed.\n");
    	  }
    	 else if ( BUTTON_5 == goertzel_bit_mask)
    	  {
    	     puts ("Button 5 pressed.\n");
    	  }
    	 else if ( BUTTON_6 == goertzel_bit_mask)
    	  {
    	     puts("Button 6 pressed.\n");
    	  }
    	 else if ( BUTTON_7 == goertzel_bit_mask)
    	  {
    	    puts ("Button 7 pressed.\n");
    	  }
    	 else if ( BUTTON_8 == goertzel_bit_mask)
    	  {
    	     puts ("Button 8 pressed.\n");
    	  }
    	 else if ( BUTTON_9 == goertzel_bit_mask)
    	  {
    		 puts("Button 9 pressed.\n");
    	  }
    	 else if ( BUTTON_STAR == goertzel_bit_mask)
    	  {
    	     puts ("Button * pressed.\n");
    	  }
    	 else if ( BUTTON_HASH == goertzel_bit_mask)
    	  {
    	     puts ("Button # pressed.\n");
    	  }

         /* Start again */
         N = 0;
         goertzel_bit_mask = 0;
 
        } /* End of if (N == 207) */
                                                                                          
    } /* End of while */

}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  End of main.c                                                           *
 *                                                                          *
 * ------------------------------------------------------------------------ */












