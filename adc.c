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
 *    adc.c
 * \author
 *    Marcus Lunden <marcus.lunden@gmail.com>
 * \desc
 *    ADC drivers for msp430g2231
 */


#include <msp430.h>
#include <isr_compat.h>
#include <stdint.h>
#include "adc.h"
/*---------------------------------------------------------------------------*/
/* the setting for ADC10CTL1 except input channel */
#define ADCCTL1_BASE          (SHS_0 | ADC10SSEL_2 | CONSEQ_0)
static const uint16_t inch[] = {INCH_0, INCH_1, INCH_2, INCH_3, INCH_4, INCH_5, INCH_6, INCH_7, INCH_10};

static volatile uint16_t adcbuf[ADC_CHANNELS];
static volatile uint8_t current_channel;  /* range 0..(ADC_CHANNELS-1) */
/*---------------------------------------------------------------------------*/
void
adc_init(void)
{
  int i;

  /* clear the adcbuf before first use */
  for(i = 0; i < 8; i += 1) {
    adcbuf[i] = 0;
  }

  /* set the whole port as ADC input */
  P1SEL = 0xff;
  P1DIR = 0x00;
  P1REN = 0x00;
/*  P1SEL |= 0xff;*/
/*  P1DIR &=~ (1<<4);*/
/*  P1REN &=~ (1<<4);*/

  /* Set up the ADC10 module to use Vcc/GND as references, sample continuously, etc */
  current_channel = 0;
  ADC10CTL0 = (SREF_0 | ADC10SHT_2 | ADC10ON | ADC10IE | MSC);
  ADC10CTL1 = (ADCCTL1_BASE | inch[current_channel]);
  
  /* all ADC channels active */
  ADC10AE0 = 0xFF;

  /* start conversion */
  ADC10CTL0 |= (ADC10SC | ENC);
}
/*---------------------------------------------------------------------------*/
/* get the latest conversion, where channel has range 0..(ADC_CHANNELS-1) */
uint16_t
adc_result(uint8_t channel)
{
  if(channel >= ADC_CHANNELS) {
    return 0;
  }
  return adcbuf[channel];
}
/*---------------------------------------------------------------------------*/
adc_bufptr_t
adc_all_results(void)
{
  return (adc_bufptr_t)&(adcbuf[0]);
}
/*---------------------------------------------------------------------------*/
ISR(ADC10, adc10_isr)
{
  /* copy the latest conversion result */
  adcbuf[current_channel] = ADC10MEM;

  /* set the new channel; ADC must be disabled before doing this */
  current_channel++;
  if(current_channel >= ADC_CHANNELS) {
    current_channel = 0;
  }
  ADC10CTL0 &= ~(ENC);
  ADC10CTL1 = (ADCCTL1_BASE | inch[current_channel]);
  ADC10CTL0 |= (ADC10SC | ENC);

/*P1.0 == A0, P1.7 == A7*/
/*P2.6, 2.7 as GPIOs*/
}
/*---------------------------------------------------------------------------*/












