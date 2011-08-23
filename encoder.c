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

#include <avr/io.h>
#include <avr/interrupt.h>
#include "encoder.h"
 
#ifndef F_CPU
#error "No F_CPU defined - cannot initialize rotary encoder"
#endif
 
#define A_VALUE     (PIND & (1<<PD2))
#define B_VALUE     (PIND & (1<<PD7))
 
volatile int8_t enc_delta;          // -128 ... 127
static int32_t value;
 
void encode_init( void )
{
 
  DDRD &= ~(1 << PD2);
  PORTD &= ~(1 << PD2);
  DDRD &= ~(1 << PD7);
  PORTD &= ~(1 << PD7);

  EIMSK |= _BV(INT0);  //Enable INT0
  EICRA |= _BV(ISC01); //Trigger on falling edge of INT0

  enc_delta=0;
  value=0;
}


ISR( SIG_INTERRUPT0 ) {
  if (A_VALUE > 0) {     // found a low-to-high on channel A
    if (B_VALUE == 0) {  // check channel B to see which way encoder is turning
      enc_delta-=1; 
    } else {
      enc_delta+=1;        
    }
  } else {                // found a high-to-low on channel A 
    if (B_VALUE == 0) {   // check channel B to see which way
      enc_delta+=1;
    } else {
      enc_delta-=1;
    }
  }
}


int32_t encode_read( void )         // read single step encoders
{
  uint8_t tmp_sreg;  // temporaerer Speicher fuer das Statusregister

  tmp_sreg = SREG;   // Statusregister (also auch das I-Flag darin) sichern
  cli();             // Interrupts global deaktivieren

  value += enc_delta;
  enc_delta = 0;

  SREG = tmp_sreg;      // Status-Register wieder herstellen 
                        // somit auch das I-Flag auf gesicherten Zustand setzen

  return value;                   // counts since last call
}
