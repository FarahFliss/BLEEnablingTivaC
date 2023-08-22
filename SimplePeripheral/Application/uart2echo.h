#ifndef UART2ECHO_DOT_H
#define UART2ECHO_DOT_H

#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART2.h>


void initializeGPIO(void);
void createUART(UART2_Params, UART2_Handle*);
char UARTInputLoop(UART2_Handle*, char*);
void test(UART2_Handle*);

#endif
