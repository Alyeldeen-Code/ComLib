
#ifndef _USART_H_
#define _USART_H_

#include <types.h>

/*
*********************************************************************************
                                TYPES
*********************************************************************************
*/

typedef struct
{
    unsigned char ID; // ID numper represent the usart umber in micro controller
    unsigned int baud_rate;
    unsigned char stop_bit;
    unsigned char parity_bit;
} usart_t;

/*
*********************************************************************************
                                FUNCTIONS
*********************************************************************************
*/
/*-----------------------------------USART_Begin----------------------------------
description: USART_Begin is a function that configrate the usart module acording
             to the usart_t object members.
---------------------------------------------------------------------------------*/
void USART_Begin(usart_t *me);
/*-----------------------------------USART_Send----------------------------------
description: USART_Send is a function that send out string with any size
             acording to the the usart_t object .
---------------------------------------------------------------------------------*/
void USART_Send(usart_t *me, unsigned char *str);
/*-----------------------------------USART_Read----------------------------------
description: USART_Read function is the function that read string for receve
             buffer with maxmum bytes = MAX_READ_STR_SIZE.
---------------------------------------------------------------------------------*/
UINT8 *USART_Read(usart_t *me);
#endif //_USART_H_