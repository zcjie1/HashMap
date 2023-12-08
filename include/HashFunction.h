#ifndef _HASH_FUNCTION_H
#define _HASH_FUNCTION_H
#include <stdint.h>

#define CRC16_Calculate(X) _CRC16_Calculate(X, 0)
 
/* CRC16 Coding & Decoding G(X) = X^16+X^12+X^5+1, but just for string ptr */
uint16_t _CRC16_Calculate(uint8_t *ptr, uint16_t crc_init);

#endif