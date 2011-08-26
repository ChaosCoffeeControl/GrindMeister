#ifndef DEBOUNCE_H
#define DEBOUNCE_H 1

/**
 * https://www.mikrocontroller.net/articles/Entprellung#Warteschleifen-Verfahren
Wenn das Makro für die gleiche Taste (Pin) an mehreren Stellen aufgerufen werden soll, muss eine Funktion angelegt werden, damit beide Aufrufe an die gleiche Zustandsvariable flag auswerten [1]:

// Hilfsfunktion
uint8_t debounce_C1( void )
{
  return debounce(PINC, PC1);
}
 
 * 
 */

/************************************************************************/
/*                                                                      */
/*                      Not so powerful Debouncing Example              */
/*                      No Interrupt needed                             */
/*                                                                      */
/*              Author: Peter Dannegger                                 */
/*                                                                      */
/************************************************************************/
 
#include <avr/io.h>
#include <util/delay.h>
 
#ifndef F_CPU
#error kein F_CPU definiert
#endif
 
#define debounce( port, pin )                                         \
({                                                                    \
  static uint8_t flag = 0;     /* new variable on every macro usage */  \
  uint8_t i = 0;                                                      \
                                                                      \
  if( flag ){                  /* check for key release: */           \
    for(;;){                   /* loop ... */                         \
      if( !(port & 1<<pin) ){  /* ... until key pressed or ... */     \
        i = 0;                 /* 0 = bounce */                       \
        break;                                                        \
      }                                                               \
      _delay_us( 98 );         /* * 256 = 25ms */                     \
      if( --i == 0 ){          /* ... until key >25ms released */     \
        flag = 0;              /* clear press flag */                 \
        i = 0;                 /* 0 = key release debounced */        \
        break;                                                        \
      }                                                               \
    }                                                                 \
  }else{                       /* else check for key press: */        \
    for(;;){                   /* loop ... */                         \
      if( (port & 1<<pin) ){   /* ... until key released or ... */    \
        i = 0;                 /* 0 = bounce */                       \
        break;                                                        \
      }                                                               \
      _delay_us( 98 );         /* * 256 = 25ms */                     \
      if( --i == 0 ){          /* ... until key >25ms pressed */      \
        flag = 1;              /* set press flag */                   \
        i = 1;                 /* 1 = key press debounced */          \
        break;                                                        \
      }                                                               \
    }                                                                 \
  }                                                                   \
  i;                           /* return value of Macro */            \
})
 
/*
   Testapplication
 */
//int main(void)
//{
//  DDRB  &= ~(1<<PB0);
//  PORTB |=   1<<PB0;
//  DDRB  |=   1<<PB2;
//  DDRB  &= ~(1<<PB1);
//  PORTB |=   1<<PB1;
//  DDRB  |=   1<<PB3;
//  for(;;){
//    if( debounce( PINB, PB1 ) )
//      PORTB ^= 1<<PB2;
//    if( debounce( PINB, PB0 ) )
//      PORTB ^= 1<<PB3;
//  }
//}
//

#endif /* DEBOUNCE_H */

