/*****************************************************************************/
/*                                                                           */
/* FILENAME                                                                  */ 
/*   goertzel.h                                                              */                           
/*                                                                           */
/* DESCRIPTION                                                               */
/*   Header file for Goertzel algorithm.                                     */
/*                                                                           */
/* REVISION                                                                  */
/*   Revision: 1.00                                                          */ 
/*   Author  : Richard Sikora                                                */ 
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* HISTORY                                                                   */
/*   Revision 1.00                                                           */
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

#ifndef GOERTZEL_H
#define GOERTZEL_H

// @ToDo 2:
// Define coefficients for "goertzel_filter" and "calculate_goertzel_output_power_v0"
// The values here correspond to a/2 in Q15 format (see formula 4.40 in DSVB script)
// Values from TI_DTMF.pdf Table 1 converted to Q15 format (<< 15)
 //#define COEFFICIENT_697_Hz  27978
 //#define COEFFICIENT_770_Hz  26956
 //#define COEFFICIENT_852_Hz  25701
 //#define COEFFICIENT_941_Hz  24219
 //#define COEFFICIENT_1209_Hz 19073
 //#define COEFFICIENT_1336_Hz 16325
 //#define COEFFICIENT_1477_Hz 13085
 //#define COEFFICIENT_1633_Hz  9314

// Values from TI_DTMF.pdf Table 2
 #define COEFFICIENT_697_Hz  27978
 #define COEFFICIENT_770_Hz  26956
 #define COEFFICIENT_852_Hz  25701
 #define COEFFICIENT_941_Hz  24219
 #define COEFFICIENT_1209_Hz 19261
 #define COEFFICIENT_1336_Hz 16525
 #define COEFFICIENT_1477_Hz 13267
 #define COEFFICIENT_1633_Hz  9093

// @ToDo 4:
// Define coefficients for "calculate_goertzel_output_power_v1"
// The values here correspond to real/imag part of twiddle factor W_N^k in Q15 format
 #define b_RE_697_Hz  -27980
 #define b_RE_770_Hz  -26956
 #define b_RE_852_Hz  -25701
 #define b_RE_941_Hz  -24219
 #define b_RE_1209_Hz -19073
 #define b_RE_1336_Hz -16325
 #define b_RE_1477_Hz -13085
 #define b_RE_1633_Hz  -9315 // 9314.8

 #define b_IM_697_Hz  17055
 #define b_IM_770_Hz  18631
 #define b_IM_852_Hz  20327
 #define b_IM_941_Hz  22072
 #define b_IM_1209_Hz 26645
 #define b_IM_1336_Hz 28412
 #define b_IM_1477_Hz 30042
 #define b_IM_1633_Hz 31416

 /* The following are the bit masks corresponding to each button push */
 #define BUTTON_1    0x0011
 #define BUTTON_2    0x0021
 #define BUTTON_3    0x0041
 #define BUTTON_4    0x0012
 #define BUTTON_5    0x0022
 #define BUTTON_6    0x0042
 #define BUTTON_7    0x0014
 #define BUTTON_8    0x0024
 #define BUTTON_9    0x0044
 #define BUTTON_STAR 0x0018
 #define BUTTON_0    0x0028
 #define BUTTON_HASH 0x0048

 void goertzel_filter_v0( short int * delay, short int input, short int coefficient );

 void goertzel_filter_v1( short int * delay, short int input, short int coefficient );
  
 short int goertzel_output_power_v0( short int * delay, short int coefficient );
 
 short int goertzel_output_power_v1(short int * delay, short int b_RE, short int b_IM);

#endif

/*****************************************************************************/
/* End of goertzel.h                                                         */
/*****************************************************************************/
