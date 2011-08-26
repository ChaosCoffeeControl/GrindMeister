/**
 * This file is part of GrindMeister.
 *
 * (c) Mathias Dalheimer <md@gonium.net>, 2011
 *
 * GrindMeister is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * GrindMeister is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GrindMeister. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "debounce.h"
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
  // Encoder A and B 
  DDRD &= ~(1 << PD2);
  PORTD &= ~(1 << PD2);
  DDRD &= ~(1 << PD7);
  PORTD &= ~(1 << PD7);
  // Encoder Pushbutton - 10k Pullup, Active High
  DDRD &= ~(1 << PD4);
  PORTD &= ~(1 << PD4);
  //PORTD |=   1<<PD4;

  /*
   * Trigger on rising edge of INT0. This seems to work more stable
   * than the falling edge. More science needed.
   */
  EIMSK |= _BV(INT0);  //Enable INT0
  EICRA |= (1 << ISC01) | (1 << ISC00); 

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

bool is_encoder_pressed() {
  if (debounce(PIND, PD4)) {
    return true;
  } else {
    return false;
  }
}

int32_t encode_read( void ) {
  uint8_t tmp_sreg;  // temporaerer Speicher fuer das Statusregister

  tmp_sreg = SREG;   // Statusregister (also auch das I-Flag darin) sichern
  cli();             // Interrupts global deaktivieren

  value += enc_delta;
  enc_delta = 0;

  SREG = tmp_sreg;      // Status-Register wieder herstellen 
                        // somit auch das I-Flag auf gesicherten Zustand setzen

  return value;                   // counts since last call
}
