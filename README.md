# The Christmas Present Defender
> A perfect first Arduino project for teaching Arduino circuits.

![Breadboard with Arduino Components](https://i.imgur.com/bdLpcQq.png)

___
### Hardware Requirements & Cost
The hardware requirements are listed below with their respective prices.
* Arduino Nano ($5.10CAD)
* MPU-6050 Gyroscope Module ($4.66CAD)
* Jumper Cables (<$1CAD)
* Mini Breadboard (~$2.80CAD)
* Buzzer ($0.89CAD)

That's right, this project can be completed for **the total cost of $13.45CAD, or $10.52USD (12/05/2020)**.
___
### Project History
This project's inception is based mostly around [the hackster.io project by David Escobar from 2016](https://www.hackster.io/daescobar/christmas-presents-intruder-detector-f10581). Unfortunately we couldn't get a hold of the exact equipment used for their version of the project in time for our usage. Thus, we decided to hit up Amazon, checked "One-Day Shipping," and hoped for the best.

We intended on using the Arduino Nano-based Christmas Present Intruder Detector in order to be a good starting project for teaching circuits to a classroom of children. It had to be simple and had to be able to be done quickly so we could be handing these things out left and right.

We decided to omit the coding for for this project, students would put together the circuit with guidance of a teacher, and then walk up to a computer with pre-written code on it, they'd be walked through what the code was doing depending on technical literacy and age, allow them to test changing certain variables, such as the frequency and duration of the buzzer or the tolerance of the alarm. 

The students would then hit the compile button, and watch the code upload. They would then be handed a USB cable and would be allowed to plug it into a computer, or a plethora of USB ports around the classroom to test it out.

___
### Functionality

The completed device's function is simple. First, the device is to be set down, and either plugged in or restarted. A 2.5 second calibration period occurs, in which acceleration measurements are taken to be recorded and averaged out. These become the acceleration values that are used to compare and detect whether the device is being moved too intensely.

After that, constant measurements are being done, and if the device exceeds a % threshold increase that is too great, it will sound the buzzer. In the original project by David Escobar, a notification alert is sent to a device, however we couldn't get a hold of WiFi modules in time for the project and didn't have the means to prepare a WiFi connected guide for the children if they chose to take the devices home. 

___

### Schematics & Code

The hardware schematic for the completed device is as follows, please feel free to omit both the transistor and 1K Ohm resistor, as we did. You should notice no difference in this use case.

![Arduino Nano Based Circuit Design](https://i.imgur.com/ces2FBo.png)

You can use any Arduino board for the project, as long as it has I2C protocol capabilities. Luckily the board we used has it through the 4th and 5th analogue pins. SDA and SCL, respectively.

The only dependency for this project is the Wire library, and it is already included by default, so you can plug-and-play the provided code to get the project running on your device. The code for this project is commented so you can go in and understand it, there is also some debugging functionality if you wish to view the code through the Arduino software's serial monitor. **You can find the code in the root directory of the GitHub project.**

*\* Please remember to adjust the buzzer's data pin in the code, and make sure the MPU-6050 gyroscope address is correct. You can use [I2C scanners](https://playground.arduino.cc/Main/I2cScanner/) if you're having trouble find the correct byte to use.* You can also adjust the `TOLERANCE` variable if you find the device to be too sensitive.
