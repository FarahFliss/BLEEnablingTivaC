#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/timer.h"
#include "utils/uartstdio.h"

#define SYS_CLK 12000000 //12MHz
#define UART0_GPIO GPIO_PORTA_BASE
#define TARGET_IS_TM4C129_RA2

uint32_t sysClock;
char ui32Loop=0;
volatile bool timeoutFlag = false;
char receivedChar ='3';
bool test;
int i;
int  ch;



void
SysClock(){
    sysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
            SYSCTL_OSC_MAIN |
            SYSCTL_USE_PLL |
            SYSCTL_CFG_VCO_480),SYS_CLK );
}

void
UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //
        MAP_UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
    }
}

int main(void){
    // Get the system clock frequency
    SysClock();

    // Enable UART0 and GPIOA peripherals
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    UARTClockSourceSet(UART0_BASE, sysClock);

    //Enable GPION and GPIOF for LED notification
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);


    // Configure GPIO pins for UART0
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1); // Rx Tx

    //UARTStdioConfig(0,115200,16000000);


    // Configure Timer0 to interrupt after a timeout period
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, sysClock * 3);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntEnable(INT_TIMER0A);


    // Configure the UART for 115,200, 8-N-1 operation.
    UARTConfigSetExpClk(UART0_BASE, sysClock, 115200,   (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
            UART_CONFIG_PAR_NONE));

    // Enable UART0
    UARTEnable(UART0_BASE);
    UARTFIFOEnable(UART0_BASE) ;

    // UART_TX_TEST
    /*
    for(i=0;i<10;i++){
        UARTCharPut(UART0_BASE, 'T');
        UARTCharPut(UART0_BASE, 'E');
        UARTCharPut(UART0_BASE, 'S');
        UARTCharPut(UART0_BASE, 'T');
        UARTCharPut(UART0_BASE, ' ');
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
        //UARTprintf("Count : %d \n",ui32Loop);
        UARTCharPutNonBlocking(UART0_BASE, ui32Loop);
        ui32Loop++;
        SysCtlDelay(SysCtlClockGet() / 3);
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0);*/

    // UART_RX_TEST

    while(1)
    {
        UARTSend((uint8_t *)"\033[2JEnter text: ", 16);
        while ( UARTCharsAvail ( UART0_BASE ) )
        {
            ch = UARTCharGetNonBlocking(UART0_BASE) ;
        }
        receivedChar = (unsigned char)( ch );

        switch (receivedChar)
        {
        case '1':
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
            SysCtlDelay(5*16000000U / 3u);
            break;

        case '2':
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
            SysCtlDelay(5*16000000u / 3u);
            break;

        case '3':
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
            SysCtlDelay(5*16000000u / 3u);
            break;

        case '4':
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
            SysCtlDelay(5*16000000u / 3u);
            break;

        default:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0, GPIO_PIN_4 | GPIO_PIN_0);
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0, GPIO_PIN_1 | GPIO_PIN_0);
            SysCtlDelay(5*16000000u / 3u);
            break;
        }



        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0, 0);
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0, 0);
        SysCtlDelay(15*16000000u / 3u);
    }
}
