#ifndef _BSP_H_
#define _BSP_H_

#include <avr/io.h>
// #include <types.h>

/*
*********************************************************************************
                                TYPES
*********************************************************************************
*/
typedef unsigned char UINT8;
typedef unsigned int UINT16;
typedef unsigned long UINT32;

/*
*********************************************************************************
                                FUNCTION
*********************************************************************************
*/
void BSP_UsartInit(UINT16 buadRate);
void BSP_UsartSendChar(UINT8 chr);

#endif //_BSP_H_