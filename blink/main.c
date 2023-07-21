#include<stdint.h>
#include<stdbool.h>
#include"driverlib/gpio.h" //GPIO functions
#include"driverlib/sysctl.h" //Clock enabling and more
#include "inc/hw_memmap.h" //Memory mapping, e.g. GPIO_PORTX_BASE @
#include "inc/hw_types.h" //HW access : direct + bit-band

#define CLK_FREQ 12000000 //12 MHz
#define GPIO_LED12 GPIO_PORTN_BASE
#define GPIO_LED34 GPIO_PORTF_BASE

#define PIN_LED1 GPIO_PIN_1
#define PIN_LED2 GPIO_PIN_0
#define PIN_LED3 GPIO_PIN_4
#define PIN_LED4 GPIO_PIN_0

void sysClock(void){
    // Configure System Clock
    SysCtlClockFreqSet(SYSCTL_XTAL_12MHZ | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN, CLK_FREQ);
}
void ConfigGPIOPort(uint32_t GPIOPORT){
    // Enable GPIO via SysCtl function
    SysCtlPeripheralEnable(GPIOPORT);
}

void ConfigGPIOPin(uint32_t GPIOPORT, uint8_t GPIOPIN, bool OUT){
    // Configure GPIO Pin Mode
    if (OUT) GPIOPinTypeGPIOOutput(GPIOPORT,GPIOPIN);
    else {
        GPIOPinTypeGPIOInput(GPIOPORT, GPIOPIN);

    }
}



int main(void)
{
//Variables
    uint32_t ui32Loop;

//Enable system Clock, GPION and GPIOF
    sysClock();
    ConfigGPIOPort(SYSCTL_PERIPH_GPION);
    ConfigGPIOPort(SYSCTL_PERIPH_GPIOF);

//Configure GPIO Output Pin Mode
    ConfigGPIOPin(GPIO_LED12,PIN_LED1 ,true);
    ConfigGPIOPin(GPIO_LED12,PIN_LED2 ,true);
    ConfigGPIOPin(GPIO_LED34,PIN_LED3 ,true);
    ConfigGPIOPin(GPIO_LED34,PIN_LED4 ,true);

//Initialize LED pins to 0
    GPIOPinWrite(GPIO_PORTN_BASE, PIN_LED1 | PIN_LED2 , 0x00);
    GPIOPinWrite(GPIO_PORTF_BASE, PIN_LED3 | PIN_LED4 , 0x00);

    while(1){
 // GPIOPinWrite writes directly into the register GPIO_DATA to light the LEDs according to their pin number
        GPIOPinWrite(GPIO_PORTN_BASE, PIN_LED1 | PIN_LED2,  PIN_LED1 | PIN_LED2); //  3rd argument: 3 = 2^0 (PN0) + 2^1 (PN1)
        GPIOPinWrite(GPIO_PORTF_BASE, PIN_LED3 | PIN_LED4,  PIN_LED3 | PIN_LED4); //  3rd argument:17 = 2^4 (PF4) + 2^0 (PF0)

       // SysCtlDelay(1000000);
        for(ui32Loop = 0; ui32Loop < 1000000; ui32Loop++);

        GPIOPinWrite(GPIO_PORTN_BASE, PIN_LED1 | PIN_LED2, 0);
        GPIOPinWrite(GPIO_PORTF_BASE, PIN_LED3 | PIN_LED4, 0);

        for(ui32Loop = 0; ui32Loop < 1000000; ui32Loop++);
    }


	return 0;
}
