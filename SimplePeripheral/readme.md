# 🔗 Implementing the peripheral role in TM4C Launch Pad via CC26x2R1 🔗

## 🍱 How to install 
### Prerequisites: 
- Code Composer Studio IDE (CCS, used version 11.1.0)
- EK-TM4C1294XL Launch Pad
- CC26x2R1
### Import the project 
1. Clone this repo
2. Open CCS IDE
3. Go to File > Open Projects From File System... 

❗ /!\ For this project, we took the simple_peripheral.c available in the Resource Explorer (View > Resource Explorer > Wireless connectivity/Embedded Software/SimpleLink CC13xx CC26xx SDK / Examples/Developement Tools/ CC26x2R LaunchPad / BLE5-Stack/ simple_peripheral/TI-RTOS7 / TI Clang Compiler/ simple_peripheral) as a base code and modified it according to our needs. /!\ 

## 🧰 Functionality 
This is a simple program enabling our Tiva C Launch Pad to play the role of a peripheral in a Bluetooth connection, thus being able to advertise, respond to scan requests and connect to a potential Scanner > Central.

## 🧠 Good to know (for newbies like me 😄) 
- **About GAP:** GAP stands for Generic _Access_ Profile. (Access to the link layer operations)  It's the BLE Stack Layer responsible for handling access modes and procedures such as:
    - Device discovery (managing advertisements) 
    - Link establishement/termination
    - Security
  In other words, it's the layer responsible for defining _how_ BLE devices connect with each other. The "Profile" in GAP refers to the usage of the protocol (or the collection of predefined services) to serve a certain goal, which is in our case, connection forming. For this goal, specific roles are defined whithin GAP:
    - Broadcaster: A BLE device that only advertises, it doesn't get linked to any other device
    - Observer: In contrary to the broadcaster, it only scans for advertisements.
    - Peripheral (slave): Like a broadcaster, it signals its presence via advertising but is also prone to establish a connection with a scanner. 
    - Central (master): With what's been said above, the central role becomes straight forward. It's a scanner and a connection initiator.
 [ GAP state diagram](https://dev.ti.com/tirex/explore/content/simplelink_cc13xx_cc26xx_sdk_6_10_00_29/docs/ble5stack/ble_user_guide/html/_images/image72.jpeg) from the TI documentation illustrates where those roles are situated in the connection lifecycle.
Based on simple_peripheral.c, the GAP layer configuration for advertising goes as follows:
    - Initialize _GapAdv_params_t_ variable. An example of such a variable can be found in ti_ble_config.c
 ![GapAdv_param_t](https://imgur.com/bx7fA52.png)
    * .eventProps : a set of flags which indicate that the advertising is connectable, legacy (non-Extended Advertising), and scannable
    * .primInt : min and max advertisement intervals
    * .primChanMap : specifies the primary advertising channel which can be any combination of 37, 38 and/or 39 (only 37 is chosen in our case)
    * .peerAddrType and .peerAddr : indicates the address type and address which can either be public or random private.
    * .xPhy : defines the physical layer for advertising
    * .sid : is the service ID
 Based on the specifications and needed requirements, we can always tweak these parameters to our convenience.
    - Create an advertisement set using_ GapAdv_create()_ which returns a handle for the advertisement set. This can be done by passing the _GapAdv_params_t_ to the function. As I can't cover everything in a single readme, it's advisable to read more about the function's parameters and get familiar with [callback functions](https://www.beningo.com/embedded-basics-callback-functions/)
    - Set Advertiser's virtual address set with _GapAdv_setVirtualAdvAddr()_ 
    - Load advertisement and scan response data (if the adv is scannable) : in _SimplePeripheral_processGapMessage()_, we can have a look at an illustrative example of advertising data
 ![AdvertData](https://imgur.com/mGeyOsB.png)
    - Set which events to send to application : via GapAdv_setEventMask()
    - Finally enable advertising calling _GapAdv_enable()_
In order to modify (_GapAdv_setParam()_) or end an advertisement (_GapAdv_destroy()_), it's recommended to disable it first using _GapAdv_disable()_
- **About GATT:** GATT stands for Generic _Attribute_ Profile and its main concern is Data exchange between BLE devices. It's a subprofile of GAP that takes care of choosing how to transfer data and pick a protocol for collecting and moving it. GATT's hierarchy goes as follows : <br> <br> <img src="https://imgur.com/4LTDT3x.png" alt= “”  height="300"> <br> <br>
There are two main GATT roles that are independent from the GAP roles which are:

    * GATT Client: a device which accesses data on the remote GATT server via read, write, notify, or indicate operations
    * GATT Server: a device which stores data locally and provides data access methods to a remote GATT client
I highly recommend reading the [Data Transfer Methods](https://docs.silabs.com/bluetooth/3.2/general/gatt-protocol/gatt-server-and-client-roles#data-transfer-methods) in this article to know more about when to use read, write, notify and indicate.


