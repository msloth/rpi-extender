/*
 * Copyright (c) 2013
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

/**
 * \file
 *    msp430-arch.h
 * \author
 *    Marcus Lunden <marcus.lunden@gmail.com>
 * \desc
 *    
 */


#ifndef __MSP430_ARCH_H__
#define __MSP430_ARCH_H__

#include <msp430.h>
#include <stdint.h>

/*--------------------------------------------------------------------------*/
/* LEDs definitions */
#define   LED_RED   (1<<0)
#define   LED_GREEN (1<<6)
#define   LED_DIR   P1DIR
#define   LED_OUT   P1OUT
#define   LEDs_INIT()  do {                                                 \
                          LED_DIR |= LED_RED | LED_GREEN;                   \
                          LED_OUT &= ~(LED_GREEN | LED_RED);                \
                       } while(0)
#define   L_ON(x)   (LED_OUT |= x)
#define   L_OFF(x)  (LED_OUT &= ~(x))
/*--------------------------------------------------------------------------*/
/* init cpu, clocks */
void msp430_arch_init(void);

/* delay for a number of cycles */
void __inline__ delay(uint16_t n);
/*--------------------------------------------------------------------------*/

#endif	/* __MSP430_ARCH_H__ */

