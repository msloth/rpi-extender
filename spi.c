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
 *    spi.c
 * \author
 *    Marcus Lunden <marcus.lunden@gmail.com>
 * \desc
 *    SPI drivers for g2231
 */


#include <msp430.h>
#include <isr_compat.h>
#include <stdint.h>
#include "spi.h"
#include "pwm.h"
#include "adc.h"

/*---------------------------------------------------------------------------*/
void
spi_init(void)
{
/* note: this is adapted to the USI present on g2231 and g2452. This differs from
    the USCI-peripherals present on eg g2553. */

  USICTL1 = USISWRST;

  /* Initialize all USI registers */
  USICTL0 |= USICKPH;
  USICTL1 |= USISSEL_2;

  /* Configure ports */
  SPI_PORT(SEL)  |= SPI_MISO | SPI_MOSI | SPI_SCL;

  SPI_PORT(SEL)  &= ~SPI_CS;
  SPI_PORT(DIR)  &= ~SPI_CS;

  /* Clear UCSWRST */
  USICTL1 &= ~USISWRST;

  /* Enable interrupts */
}
/*---------------------------------------------------------------------------*/
void
spi_send(uint8_t *buf, uint8_t len)
{
  
}
/*---------------------------------------------------------------------------*/
#if 1
ISR(USI, usi_isr)
{
  ;
}
#endif /* if 0; commented out code */
/*---------------------------------------------------------------------------*/


