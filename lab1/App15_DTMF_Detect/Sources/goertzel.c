/*****************************************************************************/
/*                                                                           */
/* FILENAME                                                                  */
/*   goertzel_algorithm.c                                                    */
/*                                                                           */
/* DESCRIPTION                                                               */
/*   Contains Goertzel algorithm for 4 x 3 telephone keyboard matrix.        */
/*                                                                           */
/* REVISION                                                                  */
/*   Revision: 1.00                                                          */
/*   Author  : Richard Sikora                                                */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* HISTORY                                                                   */
/*   Revision: 1.00                                                          */
/*   12th April 2010. Created by Richard Sikora from TMS320C5510 DSK code.   */
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


#include "goertzel.h"
#include "../config.h"

/*****************************************************************************/
/* goertzel_filter_v0()   Implementation used by TI                          */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* Calculate the Goertzel value for a single frequency.                      */
/*                                                                           */
/* INPUTS:  Parameter 1. Input / output. Array containing delay elements.    */
/*          Parameter 2. Microphone input to Goertzel algorithm.             */
/*          Parameter 3. Coefficient for required frequency.                 */
/*                                                                           */
/* RETURNS: Nothing                                                          */
/*                                                                           */
/*****************************************************************************/
void goertzel_filter_v0 ( short int * delay, short int input, short int coefficient )
{
    long product;

    product = ( (long) delay[1] * coefficient ) >> 14;

    /* The input is divided by 128 to prevent overload */

	delay[0] = (short int)( (input >> 7) + (short int) product - delay[2] );

    /* Shuffle delay elements along one place */
	delay[2] = delay[1];
	delay[1] = delay[0];
}


/*****************************************************************************/
/* goertzel_filter_v1() Modified Implementation                              */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* Calculate the Goertzel value for a single frequency.                      */
/*                                                                           */
/* INPUTS:  Parameter 1. Input / output. Array containing delay elements.    */
/*          Parameter 2. Microphone input to Goertzel algorithm.             */
/*          Parameter 3. Coefficient for required frequency.                 */
/*                                                                           */
/* RETURNS: Nothing                                                          */
/*                                                                           */
/*****************************************************************************/
// @ToDo 3:
// Alternative filter implementation that uses only two taps in global array delay[]
void goertzel_filter_v1 ( short int * delay, short int input, short int coefficient )
{
    long product;
    short int sum;

    product = ( (long) delay[0] * coefficient ) >> 14;

    /* The input is divided by 128 to prevent overload */

	sum = (short int)( (input >> 7) + (short int) product - delay[1] );

    /* Shuffle delay elements along one place */
	delay[1] = delay[0];
	delay[0] = sum;
} 

/*****************************************************************************/
/* calculate_goertzel_output_power_v0()     Method used by TI                */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* Calculate the Goertzel output power for a single frequency.               */
/*                                                                           */
/* INPUTS:  Parameter 1. Address of delay array.                             */
/*          Parameter 2. Coefficient for required frequency = a/2            */
/*                                                                           */
/* RETURNS: Goertzel value.                                                  */
/*                                                                           */
/*****************************************************************************/
short int goertzel_output_power_v0( short int * delay, short int coefficient)
{
    long product1, product2, product3;
    signed int goertzel_power;
 
	#if FILTER_IMP_VER == 0
		product1 =  ( (long) delay[1] * delay[1]);

		product2 = ( ( long) delay[2] * delay[2]);

		product3 = ( ( (long) delay[1] * coefficient ) >> 14);

		product3 =  ( product3 * delay[2]);

		goertzel_power = (short int) ((product1 + product2 - product3) >> 14-5  );

		/* Re-initialize delay. Also useful in event of instability */
		delay[1] = 0;
		delay[2] = 0;
	#else
		product1 =  ( (long) delay[0] * delay[0]);

		product2 = ( ( long) delay[1] * delay[1]);

		product3 = ( ( (long) delay[0] * coefficient ) >> 14);

		product3 =  ( product3 * delay[1]);

		goertzel_power = (short int) ((product1 + product2 - product3) >> 14-5  );

		/* Re-initialize delay. Also useful in event of instability */
		delay[0] = 0;
		delay[1] = 0;
	#endif
		 
    return goertzel_power;
}

/*****************************************************************************/
/* calculate_goertzel_output_power_v1()    Method described in DSVB script   */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* Calculate the Goertzel output power for a single frequency.               */
/*                                                                           */
/* INPUTS:  Parameter 1. Address of delay array.                             */
/*          Parameter 2. Real part of Twiddle factor for required frequency  */
/*          Parameter 3. Imag part of Twiddle factor for required frequency  */
/*                                                                           */
/* RETURNS: Goertzel value.                                                  */
/*                                                                           */
/*****************************************************************************/
// @ToDo 5:
// Implement power calculation according to Figure 4.17 in the script
short int goertzel_output_power_v1(short int * delay, short int b_RE, short int b_IM)
{
	signed int goertzel_power;
    signed long real;
    signed long imag;

    real = ( (long) delay[1] * b_RE) >> 14 + delay[0];
    imag = ( (long) delay[1] * b_IM) >> 14;

    real = real * real;
    imag = imag * imag;

	goertzel_power = (short int) ((real + imag) >> 16);

    /* Re-initialize delay. Also useful in event of instability */
	delay[1] = 0;
	delay[2] = 0;

	return goertzel_power;
}

/*****************************************************************************/
/* End of goertzel_algorithm.c                                               */
/*****************************************************************************/
