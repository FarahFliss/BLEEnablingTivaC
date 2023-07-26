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
- **About UART**:
    * UART stands for Universal Asynchronous Serial Communication, let's explain every term!
        - Universal: because UART is versatile --> it supports various data formats and baud rates [^2]
        - Asynchronous: because the receiver and the transmitter aren't synchronised (you don't say?) by a shared clock --> they instead rely on a agreed upon baud rate and a data stream (start and stop bits)
        - Receiver Transmitter: any questions?
 
    * Information is transferred 1 bit at a time and to differentiate whether it's transmitted or received, we rely on the wires withholding the information. Indeed, each UART connection has a Receiving (Rx) wire and a (Tx) Transmitting one. (refer to [fig1](#fig-anchor1)
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



[^1]: See the "blink" folder containing the Practice Code 01 for more details
[^2]: baud rate is simply the number of bits per second (received or transmitted) 
