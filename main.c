/*************************************************************************
Title:    example program for the Interrupt controlled UART library
Author:   Peter Fleury <pfleury@gmx.ch>   http://jump.to/fleury
File:     $Id: test_uart.c,v 1.4 2005/07/10 11:46:30 Peter Exp $
Software: AVR-GCC 3.3
Hardware: any AVR with built-in UART, tested on AT90S8515 at 4 Mhz

DESCRIPTION:
          This example shows how to use the UART library uart.c

*************************************************************************/

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


int main(void)
{
    unsigned int c;
    char buffer[7];
    int  num=134;

    int32_t val=0;
    encode_init();
    
    /*
     *  Initialize UART library, pass baudrate and AVR cpu clock
     *  with the macro 
     *  UART_BAUD_SELECT() (normal speed mode )
     *  or 
     *  UART_BAUD_SELECT_DOUBLE_SPEED() ( double speed mode)
     */
    uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); 
    
    /*
     * now enable interrupt, since UART library is interrupt controlled
     */
    sei();
    
    /*
     *  Transmit string to UART
     *  The string is buffered by the uart library in a circular buffer
     *  and one character at a time is transmitted to the UART using interrupts.
     *  uart_puts() blocks if it can not write the whole string to the circular 
     *  buffer
     */
    uart_puts("String stored in SRAM\n\r");
    
    /*
     * Transmit string from program memory to UART
     */
    uart_puts_P("String stored in FLASH\n\r");
    
        
    /* 
     * Use standard avr-libc functions to convert numbers into string
     * before transmitting via UART
     */     
    itoa( num, buffer, 10);   // convert interger into string (decimal format)         
    uart_puts(buffer);        // and transmit string to UART

    
    /*
     * Transmit single character to UART
     */
    uart_puts("\n\r");
    

    
    int32_t oldval=val;
    for(;;) {
      val += encode_read1();
      if (val != oldval) {
        itoa( val, buffer, 10);   // convert interger into string (decimal format)         
        uart_puts(buffer);        // and transmit string to UART
        uart_puts_P("\n\r");
        oldval=val;
      }

      //_delay_ms(200);

    }


}
