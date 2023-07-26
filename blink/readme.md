# Blinking LEDs - Practice Code 01 

## How to install 
### Prerequisites: 
- Code Composer Studio IDE (CCS, used version 12.3.0)
- EK-TM4C1294XL Launch Pad
### Import the project 
1. Clone this repo
2. Open CCS IDE
3. Go to File > Open Projects From File System... 

## Takeaways 
By reading this code, you will get to know how to :
- Configure system clock
- Configure GPIO clock via SysCtl
- Configure GPIO pins to either Output or Input
- Use GPIOPinWrite the right way

## Functionality 
This is a simple program making all 4 LEDs of our Tiva C Launch Pad blink roughly every second (delay simulated by a for loop) 

## Good to know (for newbies like me) 
You'll notice the code is always divided to 3 main parts:
1. Importing the required headers and definig macros: this covers special C libraries (such as stdbool to be able to use the boolean type in C) or libraries specific to the board such as the memory mapping, the GPIO macros etc.
2. Initializing: this is where we configure and enable the components we're using. In this example, we needed the GPIO N and F for the leds, their respective clocks and the system clock. 
3. Infinite loop: that's the most familiar part to programmers, where you curate your algorithm via the different enabled components. Here, I made the LEDs blink periodically as long as the Launch pad is powered on.

## About EK-TM4C1294XL
The TM4C1294 connected LaunchPad evaluation kit is a low-cost development platform for Arm® Cortex-M4F-based microcontrollers (MCUs). [reference: https://www.ti.com/tool/EK-TM4C1294XL]
<img src="https://energia.nu/pinmaps/img/EK-TM4C1294XL-BACK.jpg"
     alt="TM4C pins"
     style="float: left; margin-right: 10px;" />
