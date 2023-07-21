# BLE Connection Enabling in a Tiva C Launch Pad
This project encompasses enabling a BLE communication in TM4C1294 Launch Pad by connecting it to a BLE coprocessor. (CC26x2R1) I will be documenting my learning progress about Tiva C launch pads and BLE stack from scratch along with example mini projects to test. I'll mainly cover what I am learning about:  
   * Tiva C Board: EK-TM4C1294XL
   * Ultra-low power wireless MCU platform: CC26x2R
   * Bluetooth Technology
   * Serial communication: what we'll use to connect the coprocessor to the Tiva board, specifically UART
   * Debugging methodology: checking registers such as Flag Registers and Data Registers (very useful and telling!) 
   


# References 
* 📖 Intro to Bluetooth Low Energy, by Mohammad Afaneh [[Amazon link]( https://amz.run/6ucB )]
* 📎  Bluetooth Vs. Bluetooth Low Energy: What's The Difference? [[2023 Update](https://www.link-labs.com/blog/bluetooth-vs-bluetooth-low-energy)]


# Motives
BLE - which stands for Bluetooth Low Energy - allows for a lower power consumption making it ideal for IoT devices that run on batteries or have **limited power** resources. It is optimized for intermittent data transfer and can last for **extended periods** on a single battery charge. It becomes obvious that the Legacy Bluetooth is less suitable for the use case BLE was intended for but first let's define them both and set their main differences.

## Bluetooth vs BLE
Bluetooth is a short range wireless technology for communication and data exchange. It uses Radio Frequency, specifically 2.4 GHz. The Classic Bluetooth device we're familiar with is called Bluetooth BR/EDR (Basic Rate/Enhanced Data Rate) and is highly used in our day-to-day life: Headsets, earpods, car infotainement etc. This kind ofdevices is either always ON or OFF which makes it fast but not energy efficient. 

In the context of systems with energy constraints and/or meant to function for a long time without battery replacement, BLE became the wisest choice among both. Based on the "race to idle principle", a BLE device will only leave sleep mode when triggered. While it makes it unconvenient for use cases involving streaming data, it's optimal for devices that share data periodically such as sensors, door bells and more systems like Industrial monitoring systems.

## External implementation of the BLE functionality
The aim behind keeping the BLE communication duties to a dedicated processor -the coprocessor- is to preserve the TM4C1294 efficiency. 

