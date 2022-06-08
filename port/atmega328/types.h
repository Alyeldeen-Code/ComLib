#ifndef _TYPES_H_
#define _TYPES_H_

#include <bsp.h>

/*
*********************************************************************************
                                STRUCTS
*********************************************************************************
*/

typedef struct usart_t
{
    unsigned int ID;
    unsigned int baud_rate;
    unsigned int stop_bit;
    unsigned int parity_bit;
} usart_t;

#endif //_TYPES_H_