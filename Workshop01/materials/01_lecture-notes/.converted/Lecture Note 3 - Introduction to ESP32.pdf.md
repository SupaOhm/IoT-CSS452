Lecture Note 3:
Introduction to ESP32

CSS452 Internet of Things

Dr. Seksan Laitrakun
School of ICT, SIIT, Thammasat University

Outlines

1. ESP32 Specification

2. Arduino IDE Setup and Uploading

3. Basic Features of ESP32

4. WiFi Connection

2

References

• Random Nerd Tutorials: https://randomnerdtutorials.com/projects-esp32/
• Last Minute Engineers: https://lastminuteengineers.com/esp32-arduino-ide-tutorial/
• Thai Easy Elect (Thai Language): https://blog.thaieasyelec.com/espino32-article-table-

of-contents/

• ESP-IDF Programming Guide: https://docs.espressif.com/projects/esp-

idf/en/latest/esp32/index.html

3

1. ESP32 Specification

This section shows ESP32 specifications.
1.1  ESP32 by Thai Easy Electronics
1.2  ESP-WROOM-32 Chip
1.3  Pin Layout
1.4  ESP32 Resources

4

1.1 ESP32 by Thai Easy Electronics

A feature-rich MCU with integrated Wi-Fi and Bluetooth connectivity for a wide-range of
applications.

An LED connected to Pin 16

ESP-WROOM-32 Chip: (2.4 GHz Wi-Fi
and Bluetooth Combo SoC)

The RESET button

The PROGRAM button

Chip CP2104: USB to serial

LED showing the power
supply 3.3 V

The port Micro USB connected
to a computer to upload an
Arduino program

5

1.2 ESP-WROOM-32 Chip

IEEE 802.11 b/g/n (frequency band: 2.4GHz)

ESP32-WROOM-32 is a powerful, generic Wi-Fi+BT+BLE MCU module that targets a
wide variety of applications.
• ESP32 Dual-Core Tensilica LX6 Microcontroller 32-bit with the speed 240 MHz
• SRAM 520 KB
• Flash Memory 2 MB (16 Mbit)
•
• Bluetooth Dual Mode (Classic and BLE)
• 2.2V to 3.6V Operating Voltage
• On-Board PCB Antenna
• 32 GPIOs (3 x UARTs, 3 x SPI, 2 x I2S, 12 x ADC, 2 x DAC, 2 x I2C, )
• On-Board Sensors: temperature sensor, hall sensor, capacitive touch interface
•

6

1.3 Pin Layout

• Analog pins → A0 – A19

• Digital pins → GPIO

•

•

I/O pins → both input/output

I pins → only input

• 3V3 pins → voltage supply

3.3V

• GND pins → ground pins

7

1.3 Pin Functions

P1: Pin Label

Function

P2: Pin Label

Function

8

1.3 Pin Functions

P3: Pin Label

Function

P4: Pin Label

Function

9

1.3 Pin Layout

The microcontroller needs these pins to read data from input devices and to control output
devices.

10

1.4 ESP32 Resources

• Thai Easy Elect: https://blog.thaieasyelec.com/espino32-article-table-of-contents/
• Last Minute Engineers: https://lastminuteengineers.com/esp32-arduino-ide-tutorial/
• Random Nerd Tutorials: https://randomnerdtutorials.com/getting-started-with-esp32/

11

2. Arduino IDE Setup and Uploading

This section consists of
2.1  Arduino IDE Setup
2.2  Uploading your Arduino program

12

2.1  Arduino IDE Setup

1. Required Software: Arduino IDE

1. To download the Arduino IDE, go to website:

2. Choose the one that is suitable to your computer:

https://www.arduino.cc/en/Main/Software

3. For Windows OS, there are 2 choices for Arduino installation:

• If you choose Windows Installer, Arduino will automatically install all

components (need the Internet).

• If you choose Windows ZIP file, all necessary components are already in this

ZIP file.

13

2.1 Arduino IDE Setup

2. Arduino IDE Installation by Windows ZIP File

1. Unzip the file: Windows ZIP File to your computer (assume Drive C:).

2. You will get a folder arduino.

3. To run the Arduino IDE, double click on “arduino.exe” in the folder arduino.

4.

If the program asks to install some components else, answer "Yes".

14

2.1 Arduino IDE Setup

3. Arduino IDE Interface

Verify
Button

Upload
Button

Menu Bar

Serial Monitor button

Your Arduino Code

Information Window
15

2.1 Arduino IDE Setup
4. USB Driver

1. The USB driver that we need is called “CP210x USB to UART Bridge VCP driver”.
2. You can download it from this link:

https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads

3. Choose a suitable version for your OS:

3.1. CP210x Universal Windows Driver: For Windows, download and unzip this file.

• In the unzipped folder, to install, run either the file

CP210xVCPInstaller_x64.exe or the file CP210xVCPInstaller_x86 (depending
on your computer’s platform).

3.2. CP210x VCP Mac OSX Driver: For Mac OS, download and install this file.

16

2.1 Arduino IDE Setup

5. Add ESP32 Board to Arduino IDE

1. Start the Arduino IDE by running “Arduino.exe”.

2. On the menu bar, select:  File > Preferences.

3.

In the “Additional Boards Manager URLs”, fill in

https://dl.espressif.com/dl/package_esp32_index.json

4. Then, click “OK”.

5. On the menu bar, select:  Tools > Board: > Boards Manager…

17

2.1 Arduino IDE Setup

5. Add ESP32 Board to Arduino IDE

6. On the board manager, fill in:  esp32

7. You will see “esp32 by Espressif Systems”, select it to install.

8. Finally, on the menu bar, select  Tools > Board > ThaiEasyElec’s ESPino32.

9. Now, you are ready to program the ThaiEasyElec’s ESPino32.

18

2.2 Uploading Your Arduino Program

1. Write the following code on your Arduino IDE (this code will print Hello World on

the serial monitor):

The baud rate of ESP32 must be 115200
(not 9600)

19

2.2 Uploading Your Arduino Program

2. Connect ESP32 to your computer via a USB port.

3. On the menu bar of the Arduino IDE:

• Select  Tools > Board: > ThaiEasyElect’s ESPino32
• Select  Tools > Port > Your_Arduino_Com_Port

4. To upload your program to ESP32, click the upload icon.

5. On the information window (at the bottom of the Arduino IDE), whenever you see

“Connecting…” as shown below, you have to press the program button on the ESP32.

6.

If uploading the program is successful, you will see “Done uploading”.

20

2.2 Uploading Your Arduino Program

7. To open the serial monitor, click on the serial-monitor button.

Choose the baud rate to 115200

21

3. Basic Features of ESP32

This section consists of
3.1  Digital Inputs and Outputs
3.2  Analog Inputs
3.3  Analog Outputs using PWM
3.4  Built-in Touch Sensors
3.5  Built-in Hall Effect Sensor
3.6  Software Reset

22

3.1 Digital Inputs and Outputs

1. Pins

We can read a digital value and control a digital device via the GPIO pins. ESP32 can
read a digital input (0 or 1) and send a digital output (0 or 1) via the GPIO pins.
• Each pin can be referred in an Arduino program by its GPIO number. For example, the

GPIO22 pin is referred as 22 in the Arduino program.

23

3.1 Digital Inputs and Outputs

2. Send a Digital Value to a Digital Pin

There are 2 steps for sending.
1) Set the pin mode. Before we can use any digital pin, we have to declare the pin
mode (INPUT or OUTPUT) of that pin. In general, we declare it in the setup()
function. To use a digital pin as an output pin, we use this command:

where pin is the GPIO number.

pinMode(pin, OUTPUT);

2) Send a digital value. To send a digital value either 0 (LOW) or 1 (HIGH) to the pin

declared above, we use this command:

digitalWrite(pin, value);

where the value is 0 or 1 (we can also use LOW or HIGH).

Note that:
• The value “1” means that this pin will supply the HIGH voltage (around 3.3 V).
• The value “0” means that this pin will supply the LOW voltage (around 0 V).

24

3.1 Digital Inputs and Outputs

3. Read a Digital Value from a Digital Pin

There are 2 steps for reading.
1) Set the pin mode. To use a digital pin as an input pin, we use this command:

pinMode(pin, INPUT);

where pin is the GPIO number. In general, we declare it in the setup() function

2) Read a digital value. To read a digital value either 0 (LOW) or 1 (HIGH) to the pin

declared above, we use this command:

X = digitalRead(pin);

where a digital value (0 or 1) read from this pin will be stored in a variable X.

Note that:
• X=1 means that the input voltage to this pin is the HIGH voltage (around 3.3 V).
• X=0 means that the input voltage to this pin is the LOW voltage (around 0 V).

25

3.1 Digital Inputs and Outputs

Example 1

We connect a button and an LED to ESP32 as shown below.

Then, we write an Arduino code to turn on/off the LED by pressing the switch:

• Press the switch → LED on;
• Not press the switch → LED off.

26

ESP3234330LEDSWPin 3v3 of ESP3210KIf press,SW is closed.17Pin GND of ESP32Long legShort leg3.1 Digital Inputs and Outputs

Example 1 (Digital_InOut.ino)

27

3.2 Analog Inputs

1. Pins

We can read an equivalent analog value (voltage) from an input device connected to an
analog pin (labeled as A0 – A19). The input voltage 0 – 3.3 volt will be mapped to the
integers 0 – 4095 (the value that ESP32 will show you), where 0 is 0 volt and 4095 is 3.3
volt.

28

3.2 Analog Inputs

2. Read an Analog Value from an Analog Pin

To read an analog input (from an inputted device) in the ESP32 using the Arduino IDE,
we use the analogRead() function, whose syntax is as follows:

X = analogRead(pin);
where pin is the name of an ESP32 analog pin (A0 – A19) and X is a variable storing a
returned value between 0 – 4095.

29

3.2 Analog Inputs
Example 2

We connect a potentiometer to ESP32 as shown below.

Then, we write an Arduino code to read the value from this pin and show it on the serial
monitor while we rotate the potentiometer.

30

ESP32A0PotentiometerPin 3v3 of ESP32Pin GND of ESP323.2 Analog Inputs

Example 2 (Analog_In.ino)

31

3.3 Analog Outputs using PWM

1. Pins

There are several methods to control an output analog device. Here, we will PWM
method to send out (from the ESP32) an equivalent analog voltage via the PWM pins.
• PWM pins: GPIO 0-19, 21-23, 25-27, 32-33.
• The values sent out will be 0 – 255 which are equivalent to 0 – 3.3 volt.

32

3.3 Analog Outputs using PWM

2. Send an Analog Value to a PWM Pin

We have the following 3 steps.
1) We have to declare these three variables at the beginning of the Arduino code:
a) We need to choose a PWM channel. There are 16 channels from 0 to 15.
b) Then, we need to set the PWM signal frequency. For an LED, a frequency of 5000

Hz is fine to use.

c) We need to set the signal’s duty cycle resolution. For ESP32, it is 8 since we use 8-

bit resolution.

For example,

int ledChannel = 0;
int freq = 5000;
int resolution = 8;

33

3.3 Analog Outputs using PWM

2. Send an Analog Value to a PWM Pin

2)

In the setup() function,
a) we declare this setup:

ledcSetup(ledChannel, freq, resolution);
b) we will map the PWM pin and the PWM channel. As a result, the PWM signal

will be sent to this PWM pin. We will use this function:

ledcAttachPin(PWMpin, ledChannel);
where PWMpin is the GPIO number of a PWM pin and channel is the variable
defined in Step 1.

3) To send a PWM signal to the PWM pin, we control the channel by using the following

function:

ledcWrite(ledChannel, dutycycle)
where channel is the variable defined in Step 1 and the duty cycle is a value between 0
– 255 (0 is 0 volt and 255 is 3.3 volt).

34

3.3 Analog Outputs using PWM

Example 3

We connect a potentiometer and an LED to ESP32 as shown below.

Then, we write an Arduino code such that we can adjust the brightness of the LED by
rotating the potentiometer.

35

ESP32A0PotentiometerPin 3v3 of ESP32Pin GND of ESP32330LED17Long legShort leg3.3 Analog Outputs using PWM

Example 3 (Analog_PWM.ino)

Step 1: Declare variables

Step 2: Set up

Step 3: Send the command

36

3.4 Built-in Touch Sensors

1. Pins

The ESP32 has 10 capacitive touch GPIOs. These GPIOs can sense variations in anything
that holds an electrical charge, like the human skin. So they can detect variations induced
when touching a GPIO pin with a finger.
• These pins are the following GPIO pins: 0, 2, 4, 12, 13, 14, 15, 27, 32, 33.

37

3.4 Built-in Touch Sensors

2. Command to Read from a Touch Sensor

To read a value from a touch-sensor pin, we use the following command:

X = touchRead(pin);
where pin is the GPIO number of a touch-sensor pin and X stores an integer between 0
and 1023 returned from this command. When no one touch this pin, a high value will be
returned. When we touch this pin, a low value will be returned.

38

3.4 Built-in Touch Sensors

Example 4

We connect a wire to the pin GPIO32 (a touch-sensor pin) of ESP32 as shown below.

Then, we write an Arduino code to read the value from this pin and show on the serial
monitor, every 1 second.

39

3.4 Built-in Touch Sensors

Example 4 (Touch_Pin.ino)

The values given
from the touch
sensor when we
touch the wire.

40

3.5 Built-in Hall Sensor

Command

The ESP32 features a built-in hall effect sensor which is located behind the metal cap. A
hall effect sensor can detect variations in the magnetic field in its surroundings. The
greater the magnetic field, the greater the output voltage.

To read the value from the Hall sensor, we use the
command:

X = hallRead();
where X stores a returned integer between -500
and 500 from the built-in Hall sensor.

41

3.5 Built-in Hall Sensor

Example 5 (Hall_Effect.ino)

Using the code here,
ESP32 will read a value
hall-effect
from the
sensor and shown on the
serial monitor, every 1
second.

42

3.6 A Software Reset

Command and Example

We can use the following command to restart the Arduino program in ESP32:

ESP.restart();

A code example (Soft_Reset.ino) is shown below: ESP32 will restart every 10 seconds.

43

4. WiFi Connection

This section consists of
4.1  Roles of ESP32 in a WiFi Network
4.2  Commands to Connect to a WiFi Network
4.3  Commands to Set up as a Local Soft Access Point
4.4  Getting Date and Time from an NTP Server

44

4.1 Roles of ESP32 in a WiFi Network

ESP32 has a WiFi module which can communicate via a WiFi network. It can be set up
as a web client, a web server, or a local access point.

45

4.2 Commands to Connect to a WiFi Network

1) To connect WiFi by using ESP32, we need to include the header file “WiFi.h” in our

Arduino code.

2) We have the following commands to set up and connect to a WiFi network.

#include <WiFi.h>

Function
WiFi.begin(“ssid”, “password”) ESP32 will try to connect to the access point ssid by

Explanation

using the password password (the password of this
SSID).

WiFi.localIP()

This function returns ESP32’s IP address.

WiFi.mode(WIFI_STA)

Let this ESP32 work as a (WiFi) station.

46

4.2 Commands to Connect to a WiFi Network

Function

WiFi.status()

Explanation

This function returns following codes to describe what is
going on with Wi-Fi connection:

• 0 : WL_IDLE_STATUS when Wi-Fi is in process of

changing between statuses,

• 1 : WL_NO_SSID_AVAIL in case configured SSID

cannot be reached,

• 3 : WL_CONNECTED after successful connection is

established,

• 4 : WL_CONNECT_FAILED if password is incorrect,
• 6 : WL_DISCONNECTED if module is not

configured in station mode.

47

4.2 Commands to Connect to a WiFi Network

Example 6 (WiFi_Connection.ino)

The header file to connect to WiFi

Baud rate = 115200

• Set the ESP32 in a station mode.
• Set ESP32 to connect to the SSID

“Your_SSID” by using the password
“Your_Password”.

ESP32 is trying to connect to the SSID.

Show the ESP32’s IP address on the
serial monitor.

48

4.2 Commands to Connect to a WiFi Network

Example 6

The results shown on the serial monitor:

49

4.3 Commands to Set up as a Local Access Point

1) To setup ESP32 as a local access point, we need to include the header file “WiFi.h” in

our Arduino code.

#include <WiFi.h>

2) We have the following commands to set up ESP32 as a local access point.

Function

Explanation

WiFi.softAP(“ssid”, “password”,
channel, hidden)

• ssid - character string containing network SSID (max. 63

characters).

• password - optional character string with a password. For

WPA2-PSK network it should be at least 8 character long. If
not specified, the access point will be open for anybody to
connect.

• channel - optional parameter to set Wi-Fi channel, from 1 to

13. Default channel = 1.

• hidden - optional parameter, if set to true will hide SSID.

This function returns the number of stations connecting to ESP32
(which is now an access point).

50

WiFi.softAPgetStationNum()

4.3 Commands to Set up as a Local Access Point

Example 7

The following code will set up ESP32 as a local access point and show the number of
stations connecting to it.  After uploading this code, ESP32 will work as a local access
point and we can use our mobile phone to connect to it.

Key commands:

• WiFi.softAP(“Your_SSID", “Your_Password"); → To set ESP32 as an access point

with SSID “Your_SSID” and password “Your_Password”.

51

4.3 Commands to Set up as a Local Access Point
Example 7 (WiFi_SoftAccessPoint.ino)

Set this ESP32 as an access point named
Your_SSID with the password Your_Password

Return the number of stations
connecting to this access point.

52

4.4 Getting Date and Time from an NTP Server

1. Introduction

• Getting date and time is especially useful in data logging to timestamp our readings.
•

If ESP32 can access to the Internet, we can get date and time using Network Time
Protocol (NTP) and we do not need additional hardware (like an RTC clock).

• There are NTP servers like pool.ntp.org that anyone can use to request time as a client.
•
In the following code, the ESP32 is an NTP Client that requests time from an NTP
Server (pool.ntp.org).

53

4.4 Getting Date and Time from an NTP Server

Example 8 (DateTimerNTP.ino)

54

4.4 Getting Date and Time from an NTP Server

Example 8

55

4.4 Getting Date and Time from an NTP Server

Example 8

The current date and time are shown on the serial monitor.

56

4.4 Getting Date and Time from an NTP Server

Explanations

1) Once ESP32 is connected to the network, we initialize the NTP client using the

configTime() function to get date and time from an NTP server.

This function needs three input parameters, which have been defined earlier:

where ntpServer is the URL of an NTP server, gmtOffset_sec is the UTC offset for our
time zone in milliseconds (Thailand is +7 hours), and daylightOffset is the Daylight
saving time (0 for Thailand).

57

4.4 Getting Date and Time from an NTP Server

Explanations

2) The printLocalTime() custom function is to print current date & time.

•

In Line 13, the getLocalTime() function will get date and time from the NTP server
and store them in the variable timeinfo.

58

4.4 Getting Date and Time from an NTP Server

Explanations

• Line 17 prints the received date and time stored in timeinfo into to a readable

format where

59

4.4 Getting Date and Time from an NTP Server

Remark

1) We connect to the NTP server only one time at the beginning. The time later is

2)

counted by the internal clock.
If we want to store date or time in a variable, we use the strftime() function,
•

For example, we can copy the information about the hour that is on the timeinfo
structure into the timeHour variable (declared to store up to 3 characters: 2 for two
digit numbers and 1 for the terminating character) as follows

• For example, for the week day, we need to create a char variable with a length of
10 characters because the longest day of the week contains 9 characters (Saturday).

60

4.4 Getting Date and Time from an NTP Server

Remark

3) More explanations can be found here:

https://randomnerdtutorials.com/esp32-date-time-ntp-client-server-arduino/

4)

In addition, we can write an Arduino code to get Epoch/Unix Time. The Epoch Time
(also know as Unix epoch, Unix time, POSIX time or Unix timestamp) is the number
of seconds that have elapsed since January 1, 1970. The code example is shown here:
https://randomnerdtutorials.com/epoch-unix-time-esp32-arduino/

61

5. Advanced Topics to Explore More

62

5. ESP32 Over-The-Air (OTA) Updates

1. What is OTA?

2. Practical Usage

Wireless Programming

Sealed Enclosures

Replaces physical USB
cables entirely, enabling
code deployment over Wi-
Fi networks.

Update waterproof,
ruggedized, or industrial
hardware shells without
breaking gaskets.

Remote IoT Nodes

Maintain ceiling, roof, or
field-mounted setups
without physically
extracting the board.

3. Library and
Requirements

Core Library

Built directly on the
standard ArduinoOTA.h
framework for seamless
IDE network port mapping.

Non-Blocking Loop

Requires a fluid loop
architecture – traditional
blocking delay() functions
must be replaced with
millis().

63

5. More Sensors and Actuators

ESP32 can connect to many sensors and actuators.
• Temperature and Humidity Sensor:

https://randomnerdtutorials.com/esp32-dht11-dht22-temperature-humidity-sensor-
arduino-ide/

• MPU-6050 Accelerometer and Gyroscope:

https://randomnerdtutorials.com/esp32-mpu-6050-accelerometer-gyroscope-arduino/

• OLED Display:

https://randomnerdtutorials.com/esp32-ssd1306-oled-display-arduino-ide/

• Etc.

64

Questions?

65


