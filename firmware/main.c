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
#include "lcd.h"

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

  /* initialize display, cursor off */
  lcd_init(LCD_DISP_ON);
  //lcd_init(LCD_DISP_ON_CURSOR_BLINK);

  uart_puts_P("1.\n\r");
  /* 
   * Test 1:  write text to display
   */

  /* clear display and home cursor */
  lcd_clrscr();

  /* put string to display (line 1) with linefeed */
  lcd_puts("LCD Test Line 1\n");
  uart_puts_P("2.\n\r");

  /* cursor is now on second line, write second line */
  lcd_puts("Value: ");

  uart_puts_P("3.\n\r");

  int32_t oldval=val;
  for(;;) {
	val = encode_read();
	if (val != oldval) {
	  itoa( val, buffer, 10);   // convert interger into string (decimal format)         
	  uart_puts(buffer);        // and transmit string to UART
	  uart_puts_P("\n\r");
	  lcd_gotoxy(7,1);
	  lcd_puts("      ");
	  lcd_gotoxy(7,1);
	  lcd_puts(buffer);
	  oldval=val;
	}
  }
}
