#ifndef _BSP_H_
#define _BSP_H_

#include <avr/io.h>
#include <usart.h>
#include <types.h>
#include <config.h>

/*
*********************************************************************************
                                TYPES
*********************************************************************************
*/

typedef struct USART_type usart_type;
struct USART_type
{
    volatile UINT8 contRA;
    volatile UINT8 contRB;
    volatile UINT8 contRC;
    volatile UINT8 _RESEVED;
    volatile UINT8 ubrL;
    volatile UINT8 ubrH;
    volatile UINT8 dataR;
};

/*
*********************************************************************************
                                FUNCTION
*********************************************************************************
*/
void BSP_UsartInit(usart_t *me);
void BSP_UsartSendChar(const usart_t *me, UINT8 chr);
UINT8 BSP_ReadChar(usart_t *me);

#endif //_BSP_H_