#ifndef ENCODER_H
#define ENCODER_H 1

void encode_init( void );

int8_t encode_read1( void );         // read single step encoders
int8_t encode_read2( void );         // read two step encoders
int8_t encode_read4( void );         // read four step encoders

#endif /* ENCODER_H */

