/*
 * Copyright (c) 2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== uart2echo.c ========
 */
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART2.h>

/* Driver configuration */
#include "ti_drivers_config.h"


/* for exporting functions */
#include "uart2echo.h"

void initializeGPIO(){
    GPIO_init();
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
}

void createUART(UART2_Params uartParams, UART2_Handle *uart){
    UART2_Params_init(&uartParams);
    uartParams.baudRate = 115200;

    *uart = UART2_open(CONFIG_DISPLAY_UART, &uartParams);

        if (*uart == NULL)
        {
            /* UART2_open() failed */
            while (1) {}
        }
    /* LED ON --> Successful initialization */
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);
}

char UARTInputLoop(UART2_Handle *uart, char *input){
    const char echoPrompt[] = "Echoing characters:\r\n";
    while (1)
       {
           size_t bytesRead = 0;
           size_t bytesWritten = 0;
           uint32_t status     = UART2_STATUS_SUCCESS;
           char ok[] = "OK -----";

           UART2_write(*uart, echoPrompt, sizeof(echoPrompt), &bytesWritten);
           while (bytesRead == 0)
           {
               status = UART2_read(*uart, input, 1, &bytesRead);

               if (status != UART2_STATUS_SUCCESS)
               {
                   /* UART2_read() failed */
                   while (1) {}
               }
           }

           bytesWritten = 0;
           while (bytesWritten == 0)
           {
               if (*input == '\r' || *input == '\n'){
                   status = UART2_write(*uart, ok, sizeof(ok), &bytesWritten);
                   return *input;
                           }
               else return 0;

               if (status != UART2_STATUS_SUCCESS)
               {
                   /* UART2_write() failed */
                   while (1) {}
               }
           }
       }
}

void test(UART2_Handle *uart){
    char t[] = "t3addet";
    size_t bytesWritten;
    UART2_write(*uart, t, sizeof(t), &bytesWritten);
}


/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    char input;
    char test;
    UART2_Handle uart;
    UART2_Params uartParams;
    size_t bytesRead;
    size_t bytesWritten = 0;


    /*Initialize GPIO */
    initializeGPIO();

    /*Create UART, Blocking default mode */
    createUART(uartParams, &uart);

    /* Loop forever until we hit ENTER*/
    test = UARTInputLoop(&uart, &input);
    return 0;
}

