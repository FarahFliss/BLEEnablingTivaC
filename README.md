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
* 📚 Texas Instruments Technical Documents [[Search Technical Documents here](https://www.ti.com/technical-documents/techdoc/results?viewType=mostuseful&rootFamilyId=64&familyId=64&docCategoryId=1&litCount=all)]


# Motives
BLE - which stands for Bluetooth Low Energy - allows for a lower power consumption making it ideal for IoT devices that run on batteries or have **limited power** resources. It is optimized for intermittent data transfer and can last for **extended periods** on a single battery charge. It becomes obvious that the Legacy Bluetooth is less suitable for the use case BLE was intended for but first let's define them both and set their main differences.

## Bluetooth vs BLE
Bluetooth is a short range wireless technology for communication and data exchange. It uses Radio Frequency, specifically 2.4 GHz. The Classic Bluetooth device we're familiar with is called Bluetooth BR/EDR (Basic Rate/Enhanced Data Rate) and is highly used in our day-to-day life: Headsets, earpods, car infotainement etc. This kind ofdevices is either always ON or OFF which makes it fast but not energy efficient. 

In the context of systems with energy constraints and/or meant to function for a long time without battery replacement, BLE became the wisest choice among both. Based on the "race to idle principle", a BLE device will only leave sleep mode when triggered. While it makes it unconvenient for use cases involving streaming data, it's optimal for devices that share data periodically such as sensors, door bells and more systems like Industrial monitoring systems.

## External implementation of the BLE functionality
The decision to offload Bluetooth Low Energy (BLE) communication duties to a dedicated coprocessor, rather than handling them on the main processor (TM4C1294), is primarily aimed at preserving the efficiency and performance of the TM4C1294 microcontroller allowing it to focus on its core tasks.

- **Power Efficiency:** BLE communication often involves periodic transmissions and receptions of data, which can consume a significant amount of power. By using a separate coprocessor for handling BLE tasks, the main processor can remain in a low-power state for longer periods. This leads to overall power savings and helps prolong the battery life in battery-powered devices.

- **Processing Load:** The TM4C1294 is a general-purpose microcontroller that may already be handling a variety of tasks, such as running the main application, interfacing with other peripherals, and managing system operations. Adding the responsibility of handling BLE communication on top of these tasks can place a heavy processing load on the main processor, potentially leading to reduced performance or increased response time for critical tasks.

- **Parallelism and Responsiveness:** By employing a dedicated coprocessor for BLE communication, it is possible to execute Bluetooth-related tasks in parallel with other operations performed by the main processor. This parallelism ensures that the main processor can focus on its primary tasks, enhancing the overall responsiveness of the system.

- **Simplified Design and Development:** Separating BLE communication onto a coprocessor allows for a cleaner system design and modular architecture. The main processor can interact with the coprocessor through well-defined interfaces and APIs, making it easier to manage and maintain the codebase.

- **Resource Sharing:** The coprocessor is likely optimized for BLE communication tasks and might include hardware accelerators or specialized instructions to efficiently handle Bluetooth protocols. By leveraging this specialized hardware, the main processor can save its own resources for other critical tasks, improving the system's overall efficiency.

 - **Firmware Updates:** If the coprocessor's firmware needs updating to address bugs or add new features, it can often be updated independently of the main processor's firmware. This separation allows for easier firmware maintenance and updates.

- **Security:** Isolating BLE communication to a dedicated coprocessor can also enhance security. By minimizing the direct interaction of the main processor with the BLE stack and radio, potential vulnerabilities are limited, making it harder for malicious actors to exploit the system.


