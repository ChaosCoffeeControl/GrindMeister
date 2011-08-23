/**
 * This file is part of GrinderTimer.
 *
 * (c) Mathias Dalheimer <md@gonium.net>, 2011
 *
 * GrinderTimer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * GrinderTimer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GrinderTimer. If not, see <http://www.gnu.org/licenses/>.
 *
 */

/* define CPU frequency in Mhz here if not defined in Makefile */
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "uart.h"
#include "encoder.h"

/* 9600 baud */
#define UART_BAUD_RATE      9600      

int main(void) {
  unsigned int c;
  char buffer[7];
  int  num=134;

  int32_t val=0;
  encode_init();

  uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); 

  sei();

  uart_puts_P("GrinderTimer is booting.\n\r");

  int32_t oldval=val;
  for(;;) {
    val = encode_read();
    if (val != oldval) {
      itoa( val, buffer, 10);   // convert interger into string (decimal format)         
      uart_puts(buffer);        // and transmit string to UART
      uart_puts_P("\n\r");
      oldval=val;
    }
  }
}
