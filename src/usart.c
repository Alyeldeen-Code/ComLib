#include <usart.h>
#include <bsp.h>

UINT8 *B[MAX_READ_STR_SIZE];

void USART_Begin(usart_t *me)
{
    BSP_UsartInit(me);
}

void USART_Send(usart_t *me, UINT8 *str)
{
    UINT8 *temp = str;
    while (*temp != '\0')
    {
        BSP_UsartSendChar(me, (char)*temp);
        temp++;
    }
    BSP_UsartSendChar(me, (char)'\n');
}

UINT8 *USART_Read(usart_t *me)
{
    volatile UINT8 chr = BSP_ReadChar(me);

    UINT8 *str;
    UINT8 *strp_ret;
    str = strp_ret = (UINT8 *)&B[0];
    while (chr != '\0')
    {
        *str = chr;
        chr = BSP_ReadChar(me);
        ++str;
    }
    *str = (UINT8)'\0';
    return strp_ret;
}
