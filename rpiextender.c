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
 *    rpiextender.c
 * \author
 *    Marcus Lunden <marcus.lunden@gmail.com>
 * \desc
 *    Raspberry Pi extender, main file. Event based, so just enters LPM.
 */
/*---------------------------------------------------------------------------*/
#include <msp430.h>
#include "msp430-arch.h"
#include "adc.h"
#include "pwm.h"

#if USI_SPI
#include "spi-usci.h"
#else   /* USI_SPI */
#if USCI_SPI
#include "spi-usi.h"
#endif  /* USCI_SPI */
#endif  /* USI_SPI */
/*---------------------------------------------------------------------------*/
void
main(void) {
  msp430_arch_init();
  adc_init();
  pwm_init();
  spi_init();

  while (1) {
    /* event based, everything happens in the interrupt service routines respectively:
        spi - handles communication requests from SPI master (Raspberry PI)
        adc - samples all channels, puts results in ADC buffer
        pwm - controlling PWM on any active PWM pins
     */
  }
}
/*---------------------------------------------------------------------------*/
















