#include <bsp.h>
#include <avr/interrupt.h>

usart_CBL UsartTbl[MAX_USART_SUPPORT];

typedef struct
{
    usart_type *addr;
    volatile UINT8 RX_buffer[RX_BUFFER_MAX_SIZE];
    volatile UINT8 RX_head;
    volatile UINT8 RX_tail;
    volatile UINT8 RX_bufSize;
} usart_CBL; // USART Controle block


static UINT16 _set_ubrr(UINT16 paud_rate)
{
    UINT16 temp;
    UINT32 freq = F_CPU;
    temp = (freq / 16 / paud_rate - 1);
    return temp;
}

static usart_type *_get_addr(UINT8 ID)
{
    usart_type *addr;
    switch (ID)
    {
    case 0:
        addr = (usart_type *)0xC0;
        break;
    case 1:
        addr = (usart_type *)0xC8;
        break;
    default:
        addr = (usart_type *)0xC0;
        break;
    }
    return addr;
}

void BSP_UsartInit(usart_t *me)
{
    UINT16 temp;
    usart_CBL *us = &UsartTbl[me->ID];

    us->addr = _get_addr(me->ID);

    temp = _set_ubrr(me->baud_rate);
    us->addr->ubrH = (UINT8)(temp >> 8);
    us->addr->ubrL = (UINT8)temp;

    us->addr->contRB |= (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);

    us->addr->contRC |= (3 << UCSZ00);

    //  must initialize
    sei();
}

void BSP_UsartSendChar(const usart_t *me, UINT8 chr)
{

    while (!(UsartTbl[me->ID].addr->contRA & (1 << UDRE0)))

        ;

    UsartTbl[me->ID].addr->dataR = chr;
}

// resceve complete interrupt

ISR(USART_RX_vect)
{
    UINT8 data;
    UINT8 index;
    usart_CBL *usart = &UsartTbl[0];
    if (usart->RX_bufSize != RX_BUFFER_MAX_SIZE)
    {
        index = usart->RX_tail % RX_BUFFER_MAX_SIZE;
        data = usart->addr->dataR;
        usart->RX_buffer[index] = data;
        ++index;
        ++(usart->RX_bufSize);
        usart->RX_tail = index;
    }
}

UINT8 BSP_ReadChar(usart_t *me)
{
    UINT8 data;
    UINT8 index;
    usart_CBL *usart = &UsartTbl[me->ID];
    volatile UINT32 count = 20000;
    while (count)
    {
        count--;
    }

    if (usart->RX_bufSize != 0)
    {
        index = usart->RX_head % RX_BUFFER_MAX_SIZE;
        data = usart->RX_buffer[index];
        ++index;
        --(usart->RX_bufSize);
        usart->RX_head = index;
        return data;
    }
    return '\0';
}