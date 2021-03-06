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
#ifndef ENCODER_H
#define ENCODER_H 1

#include <stdbool.h> // C99

void encode_init( void );
int32_t encode_read( void );
bool is_encoder_pressed( void );

#endif /* ENCODER_H */

