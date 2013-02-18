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
 *    msp430-arch.c
 * \author
 *    Marcus Lunden <marcus.lunden@gmail.com>
 * \desc
 *    
 */


#include <stdio.h>
#include <msp430.h>
#include <isr_compat.h>

#include "msp430-arch.h"
/*---------------------------------------------------------------------------*/
static void clk_init(void);
static void ports_init(void);
/*---------------------------------------------------------------------------*/
void
msp430_arch_init(void)
{
  /* stop WDT and init everything */
  WDTCTL = WDTPW + WDTHOLD;
  ports_init();
  LEDs_INIT();
  clk_init();
  __eint();
}
/*---------------------------------------------------------------------------*/
/* Delay Routine from mspgcc help file. Delay 0..65535 cycles, corresponding
  to 0..65 ms @ 1 MHz. */
void __inline__
delay(uint16_t n)
{
  if (n > 0) {
    __asm__ __volatile__ (
    "1: \n"
    " dec %[n] \n"
    " jne 1b \n"
          : [n] "+r"(n));
  }
}
/*---------------------------------------------------------------------------*/
// Timer A0 interrupt service routine
#if 0
#define PORT1_VECTOR        (0x0004)  /* 0xFFE4 Port 1 */
#define PORT2_VECTOR        (0x0006)  /* 0xFFE6 Port 2 */
#define USI_VECTOR          (0x0008)  /* 0xFFE8 USI */
#define ADC10_VECTOR        (0x000A)  /* 0xFFEA ADC10 */
#define TIMER0_A1_VECTOR    (0x0010)  /* 0xFFF0 Timer0_A CC1, TA */
#define TIMER0_A0_VECTOR    (0x0012)  /* 0xFFF2 Timer0_A CC0 */
#define WDT_VECTOR          (0x0014) /* 0xFFF4 Watchdog Timer */
#define COMPARATORA_VECTOR  (0x0016) /* 0xFFF6 Comparator A */
#define NMI_VECTOR          (0x001C) /* 0xFFFC Non-maskable */
#define RESET_VECTOR        (0x001E) /* 0xFFFE Reset [Highest Priority] */
#endif
/*--------------------------------------------------------------------------*/
static void
ports_init(void)
{
  /* set everything to dig GPIO, ouutput, low */
  P1SEL = 0;
  P1DIR = 0xff;
  P1OUT = 0;
  P1IE = 0;

  P2SEL = 0;
  P2DIR = 0;
  P2OUT = 0;
  P2IE = 0;
}
/*---------------------------------------------------------------------------*/
static void
clk_init(void)
{
  /* set clock speed */
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;

  /* set divider */
  BCSCTL2 &= ~(DIVS_0);
}
/*---------------------------------------------------------------------------*/
ISR(TIMER0_A0, timer0a0_isr)
{
  ;
}
/*---------------------------------------------------------------------------*/
ISR(WDT, wdt_isr)
{
  ;
}
/*---------------------------------------------------------------------------*/
