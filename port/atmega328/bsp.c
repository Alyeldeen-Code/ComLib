#include <bsp.h>

// typedef struct USART_type usart_type;
// struct USART_type
// {
//     UINT8 contRA;
//     UINT8 contRB;
//     UINT8 contRC;
//     UINT8 _RESEVED;
//     UINT8 ubrH;
//     UINT8 ubrL;
//     UINT8 dataR;
// };

UINT16 _set_ubrr(UINT16 paud_rate)
{
    UINT16 temp;
    UINT32 freq = F_CPU;
    temp = (freq / 16 / paud_rate - 1);
    return temp;
}

// usart_type *_get_addr(const usart_t *me)
// {
//     usart_type *addr;
//     switch (me->ID)
//     {
//     case 0:
//         addr = (usart_type *)0xC0;
//         break;
//     case 1:
//         addr = (usart_type *)0xC8;
//         break;
//     default:
//         addr = (usart_type *)0xC0;
//         break;
//     }
//     return addr;
// }

void BSP_UsartInit(UINT16 buadRate)
{
    UINT16 temp;
    temp = _set_ubrr(buadRate);

    UBRR0H = (UINT8)(temp >> 8);
    UBRR0L = (UINT8)temp;

    UCSR0B |= (1 << TXEN0);

    UCSR0C |= (3 << UCSZ00);
}

void BSP_UsartSendChar(UINT8 chr)
{
    // usart_type *addr;
    // addr = _get_addr(me);
    while (!(UCSR0A & (1 << UDRE0)))

        ;

    UDR0 = chr;
}
