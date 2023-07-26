# 🔗 Testing UART serial connection - Practice Code 02 🔗

## 🍱 How to install 
### Prerequisites: 
- Code Composer Studio IDE (CCS, used version 11.1.0)
- EK-TM4C1294XL Launch Pad
### Import the project 
1. Clone this repo
2. Open CCS IDE
3. Go to File > Open Projects From File System... 

## 📔 Takeaways 
By reading this code, you will get to know how to :
- [x] Configure system clock [^1]
- [x] Configure GPIO clock via SysCtl [^1]
- [x] Configure GPIO pins to either Output or Input [^1]
- [x] Use GPIOPinWrite the right way [^1]
- [ ] Enable UART0 and its corresponding GPIO
- [ ] Enable UART0's clock
- [ ] Configure UART GPIO pins
- [ ] Configure a timer (to be continued)
- [ ] Configure the UART baud rate, data bits, parity, stop bits and flow control
- [ ] Test UART Tx
- [ ] Test UART Rx

## 🧰 Functionality 
This is a simple program enabling our Tiva C Launch Pad's UART connection (UART0) and testing both its transmitting and receiving functionality.

## 🧠 Good to know (for newbies like me 😄) 
- It's important to know that every component of the the launch pad should be configured and ** then enabled**. Thus, using UART0 in our case was preceded by configuring its clock, GPIO and pins.
- **About UART:**
    * UART stands for Universal Asynchronous Serial Communication, let's explain every term!
        - Universal: because UART is versatile --> it supports various data formats and baud rates [^2]
        - Asynchronous: because the receiver and the transmitter aren't synchronised (you don't say?) by a shared clock --> they instead rely on a agreed upon baud rate and a data stream (start and stop bits)
        - Receiver Transmitter: any questions?
 
    * Information is transferred 1 bit at a time and to differentiate whether it's transmitted or received, we rely on the wires withholding the information. Indeed, each UART connection has a Receiving (Rx) wire and a (Tx) Transmitting one. (refer to [fig1](#fig-anchor1) )
    * As shown in Fig 1, in order for a UART communication to function, we need the endpoints to share a **common GND** (ground) for several reasons:
        - **A stable reference voltage level:** both endpoints have the same baseline to determine the logical values of the data. Both will recognise 1s and 0s the same way.
        - **A proper voltage level translation:** since UART communication is often between two devices with different power supplies, having a common ground ensures that the data transmitted from one device is correctly interpreted by the receiving device.
        - **To eliminates ground loops:** in case where the devices have different ground references, there may be a variation that may corrupt data and/or cause interference.
        - **To improve noise immunity:** common ground protects against the effects of electrical noises and therefore, ensures the data integrity.

<div align="center">
  
| ![UART wiring](https://vanhunteradams.com/Protocols/UART/uart_hardware.png)  |
|:--:| 
| Fig 1: UART Hardware ([Source](https://vanhunteradams.com/Protocols/UART/UART.html)) <a id="fig-anchor1"></a> |

</div>

- **Testing UART Tx:**
    * After importing the project, go to uart.c
    * You'll find commented sections //UART_TX_TEST and //UART_RX_TEST. We're going to focus on the //UART_TX_TEST
    * Select the section below if it's commented and CTRL+7 to make it executable
    * This code snippet will let us check if the Board UART Tx. We're going to ask the board to send us a test message periodically.
    * In order to see the message, we need a serial terminal which is a computer program or hardware device that allows communication with another device or computer over a serial interface. In our case we're using a software like PuTTY, Realterm or the serial terminal embedded in Code Composer Studio. [^3]
    * In this example, we used Realterm just to show you the UART set configurations, they must match with the board's configuration. <br><br>
    ![realterm](https://imgur.com/LsoELTc.png) <br><br>
    * In order to know/modify the board's serial communication configurations, if you're on windows 10 like me, go to Device Manager > Ports (COM & LPT) <br> <br>
    ![deviceman](https://imgur.com/2yAtsex.png)
<br> <br>
    * If you double click on the right port (which is Stellaris, so COM10 in my case) then go to Port settings, you can adjust the parameters like so: <br> <br>
    ![param](https://imgur.com/0AEd3JF.png) <br><br>
    * These are the most frequently used parameters, just make sure they're the same in both sides for now ( [to know more](https://www.analog.com/en/analog-dialogue/articles/uart-a-hardware-communication-protocol.html) ) 
    * If everything goes well, (hopefully!) we should see the test message like the picture above. If you happen to see gibberish, this most likely mean the parameters don't match (the data is misinterpreted)
 
-  **Testing UART Rx:**
    * Now let's put the //UART_TX_TEST section in comments and focus on //UART_RX_TEST code snippet
    * Same as before, we're monitoring what's going on via the Serial terminal of your choice
    * In this example, we used PuTTY
    * The code will prompt the user to enter a text
    * Reading the code, it's obvious that if you enter 1, LED 1 will be enabled, if you enter 2 etc ... and if you enter anything else, the 4 LEDs will turn on.
    * Everytime the PC gets your input, it sends it to the board and the board responds back by echoing the character you just typed and simultaneously turn on the corresponding LEDs
    * After the given delay, all LEDs will get turned off to signal to the user that he can type another character (indicating the start of the next loop) 
    * This allows us to know that the UART communication is receiving the right data


[^1]: see the "blink" folder containing the Practice Code 01 for more details
[^2]: baud rate is simply the number of bits per second (received or transmitted) 
[^3]: to use the CCS serial terminal, go to View > Terminal, click on the Open Terminal (or CTRL+Alt+SHIFT+T) 
