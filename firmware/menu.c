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

#include <avr/interrupt.h>
#include <util/delay.h>
#include "menu.h"
#include "lcd.h"

typedef void (*MenuFnct) (int);
 
struct MenuEntry {
  char     Text[20];
  MenuFnct Function;
  int      ArgumentToFunction;
};

void HandleEdit (int arg) {
  lcd_clrscr();
  lcd_puts("LCD Edit\n");
}
 
void HandleCopy (int arg) {
  lcd_clrscr();
  lcd_puts("LCD Copy\n");
}
 
void HandlePaste (int arg) {
  lcd_clrscr();
  lcd_puts("LCD Paste\n");
}

struct MenuEntry MainMenu[] =
{
   // Der Funktion HandleEdit soll beim Aufruf 23 mitgegeben werden
   { "Edit",  HandleEdit,  23 },
   { "Copy",  HandleCopy,   0 },
   { "Paste", HandlePaste,  0 }
};

#define ARRAY_SIZE(X) (sizeof(X) / sizeof(*(X)))

void do_menu (int NrEntries, struct MenuEntry Menu[]) {
  for (int i=0; i<NrEntries; i++) {
    Menu[i].Function (Menu[i].ArgumentToFunction);
    _delay_ms(1000);
  }
}

void loop_menu(void) {
  for(;;) {
    do_menu(ARRAY_SIZE (MainMenu), MainMenu);
  }
}
