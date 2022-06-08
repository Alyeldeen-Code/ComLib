
#include <usart.h>

void USART_Begin(UINT16 buadRate)
{
    BSP_UsartInit(buadRate);
}

void USART_Send(UINT8 *str)
{
    UINT8 *temp = str;
    while (*temp != '\0')
    {
        BSP_UsartSendChar((char)*temp);
        temp++;
    }
    BSP_UsartSendChar((char)'\15');
}