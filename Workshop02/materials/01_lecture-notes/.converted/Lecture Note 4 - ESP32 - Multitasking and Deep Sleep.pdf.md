Lecture Note 4:
ESP32 – Multitasking and
Deep Sleep

CSS452 Internet of Things

Dr. Seksan Laitrakun
School of ICT, SIIT, Thammasat University

1

Outlines

1. Multitasking: Timers and Interrupts

2. Multitasking: Task Management and Dual-Core Execution

3. Deep Sleep

4. Advanced Topics

2

Multitasking in Microcontrollers

• Multitasking in a microcontroller is the ability to run multiple software routines or jobs

seemingly at the same time by rapidly switching the processor between them.

• ESP32 supports multitasking operations.
•
• We study two task categories.

In this lecture note, we will investigate on writing programs for multitasking problems.

• Timing-Based Tasks

• Definition: Actions that happen at regular, set time intervals.
• How it works: Uses a hardware timer, a clock, or a delay function to count time.
• Example: Blinking an LED every 2 seconds.

• Event-Based Tasks

• Definition: Actions that happen only when an external or internal event occurs.
• How it works: Uses interrupts or status checks to listen for a change.
• Example: Turning on an LED when a user presses a button.

3

In Sections 1 & 2, use a variety of Arduino commands
to solve this multitasking problem.
We connect a button and two LEDs to ESP32 as shown below. Note that, by connecting the
switches in this way, pressing the switch gives the LOW logic at the ESP32 pin.

Then, we write an Arduino code to do the following 2 tasks in parallel: to control the LED1 and
LED2.
• Task 1 (timing-based task): LED1 is alternatively turned on for 2 seconds and turned off for 2

seconds.

• Task 2 (event-based task): LED2 is turned on by pressing the switch; otherwise, it is turned off.
4

ESP3234330LED1SWPin 3v3 of ESP3210KIf not press,SW is open.If press,SW is closed.16Pin GND of ESP32Long legShort leg330LED217Long legShort legIn Section 3: Deep Sleep

• Deep sleep is an ultra-low power mode in a microcontroller that turns off the main

CPU core and most internal peripherals to save battery life.
• We will study a simple command to put an ESP32 to deep sleep.
•

In addition, we will study four techniques (commands) to wake the ESP32 up from a
deep sleep:
• Timer Wake-up
• Touch Wake-up
• Ext0 External Wake-up
• Ext1 External Wake-up

5

References

• Random Nerd Tutorials: https://randomnerdtutorials.com/projects-esp32/
• Last Minute Engineers: https://lastminuteengineers.com/esp32-arduino-ide-tutorial/
• Thai Easy Elect (Thai Language): https://blog.thaieasyelec.com/espino32-article-table-

of-contents/

• ESP-IDF Programming Guide: https://docs.espressif.com/projects/esp-

idf/en/latest/esp32/index.html

6

1. Multitasking: Timers and Interrupts

Multitasking is a technique to write a code such that several jobs will be
executed concurrently (where the CPU jumps from one job to another job). This
section consists of
1.1  Timers for Timing-Based Tasks
1.2  Interrupts for Event-Based Tasks

7

1.1 Timers for Timing-Based Tasks

1) Problem:

•
In earlier examples, when we turn on or off an LED, we use the delay() function.
• However, the delay() function will block our code and not allow ESP32 to do

•

anything else for the specified time duration.
For example, delay(1000) means the ESP32 will stay at this command for 1
second.

2) Solution:

• On the other hand, to not waste the CPU time and if we have other work run

concurrently, we could use a timer which is the millis() function.

• The millis() function. The millis() function will return the number of milliseconds

that have passed since the program first started. For example,

where X stores the number of milliseconds. An example is shown in the next
slide.

8

X = millis();

1.1 Timers

Example 1

We connect a button and two LEDs to ESP32 as shown below. Note that, by connecting the
switches in this way, pressing the switch gives the LOW logic at the ESP32 pin.

Then, we write an Arduino code to do the following 2 tasks in parallel: to control the LED1 and
LED2.:
• Task 1 (timing-based task): LED1 is alternatively turned on for 2 seconds and turned off for 2

seconds.

• Task 2 (event-based task): LED2 is turned on by pressing the switch; otherwise, it is turned off.
9

ESP3234330LED1SWPin 3v3 of ESP3210KIf not press,SW is open.If press,SW is closed.16Pin GND of ESP32Long legShort leg330LED217Long legShort leg1.1 Timers

Example 1 (Ex_millis.ino)

Use milli(); technique

10

1.1 Timers

Example 1

A demonstration video is shown below.

11

1.2 Interrupts for Event-Based Tasks

•

•

Interrupts are useful for making things happen automatically in microcontroller
programs, and can help solve event-based problems.
• With interrupts we do not need to constantly check the current value of a pin.
In this section, we will apply a pin-change interrupt.
• With pin-change interrupt, when a voltage change is detected at the pin, an event is

triggered (a function is called).

• Other types of interrupts are available such as timer interrupts
(https://www.arduino.cc/reference/en/libraries/timerone/)

12

1.2 Interrupts

1. Pin-Change Interrupt

To set an interrupt in the Arduino IDE, we use the attachInterrupt() function (put it in the
setup() function), whose syntax is

attachInterrupt(digitalPinToInterrupt(GPIO), function, mode);

Parameter

digitalPinToInterrupt(GPIO)

function

mode

Meaning

A function is to set the actual GPIO as an interrupt pin. The GPIO pins
useable as interrupt pins are show in the next page. This GPIO pin must be
declared as an INPUT pin.

The second argument is the name of the function that will be called every
time the interrupt is triggered.

The third argument is the mode when the interrupt is triggered. There are 5
different modes:

• LOW: to trigger the interrupt whenever the pin is LOW.
• HIGH: to trigger the interrupt whenever the pin is HIGH.
• CHANGE: to trigger the interrupt whenever the pin changes value –

for example from HIGH to LOW or LOW to HIGH.
• FALLING: for when the pin goes from HIGH to LOW.
• RISING: to trigger when the pin goes from LOW to HIGH.

13

1.2 Interrupts

1. Pin-Change Interrupt

The GPIO pins useable as interrupt pins are all GPIO pins except the pins GPIO6 –
GPIO11.

They cannot be
used as interrupt
pins.

14

1.2 Interrupts
Example 2

We connect a button and two LEDs to ESP32 as shown below (similar to Example 1).

Then, we write an Arduino code to do the following 2 tasks in parallel: to control the LED1 and
LED2.
• Task 1 (timing-based task): LED1 is alternatively turned on for 2 seconds and turned off for 2

seconds.

• Task 2 (event-bases task): LED2 is toggled when we press and release the switch (we will use

an interrupt for this task). (Note that this task is differed from Example 1.)

15

ESP3234330LED1SWPin 3v3 of ESP3210KIf not press,SW is open.If press,SW is closed.16Pin GND of ESP32Long legShort leg330LED217Long legShort leg1.2 Interrupts

Example 2 (Ex_Interrupts.ino)

By using an interrupt we can modify the code previously as follows.

Step 1: Create a function.

16

1.2 Interrupts

Example 2 (Ex_Interrupts.ino)

Step 2: Declare a pin-change interrupt.

17

1.2 Interrupts
Example 2

A demonstration video is shown below.

18

Summary

Topic

Detail

Command

1.1 Timers

Timing-based tasks

millis();

1.2 Interrupt

Event-based tasks

attachInterrupt(digitalPinToInterrupt(GPIO),
function, mode);

19

2. Multitasking: Task Management

and Dual-Core Execution

This section consists of
2.1  Task Management
2.2  ESP32 Dual Core

20

2.1 Task Management

Commands

• A problem: As we have seen previously in Section 1, we might assign ESP32 many
tasks and, then, we have to organize them carefully such that these tasks can be
executed concurrently.
• Specifically, in Example 1 (in Page 10), the programmer designs the order of task

execution as follows: execute Task 1 first and then go to execute Task 2.

• A solution: In addition to managing and scheduling these jobs by ourselves, we can

define each job as a task (= a process) and let ESP32 manage all tasks by itself.
• To do this way, we have the following procedures.

21

2.1 Task Management

Commands

1) We create a task function for each task. This function is similar to the functions we

have declared before.

void TaskName (void * parameter) {

// Here, what ESP32 will do in this task.
…
vTaskDelete(NULL);

}
Note that:
• The vTaskDelete(NULL) function is needed to kill the task when finish.
• To run this task infinitely, we must create an infinite loop as shown below.

void TaskName (void * parameter) {

for (;;) {

// Here, what ESP32 will do in this job repeatedly.

…
}
vTaskDelete(NULL);

}

22

2.1 Task Management

Commands

2)

In the setup() function, we have to declare each task by using the xTaskCreate() function whose syntax
is, for example,

xTaskCreate( TaskName,

“TaskName”,
10000,
NULL,
1,
NULL

);

Meaning

/* Task function. */
/* Task name. */
/* Stack size in bytes. */
/* Parameter passed as input of the task */
/* Priority of the task. */
/* Task handle. */

It is the name of the function for this job that we will ask ESP32 to do

It is the string of the function name

Parameter

Task function

Task name

Stack size in bytes

It is the amount of memory that is allocated for this task

Parameter

a list of inputs which will be passed to the function above

Priority of the task

It is a number between 0 – 24 (higher number → higher priority which will be
executed first when ESP32 needs to choose)

Task handle

This parameter stores an handle that can be used for latter reference of the task on
calls to functions (for example, to delete a task or change its priority).

23

2.1 Task Management

Example 3

We connect a button and two LEDs to ESP32 as shown below (similar to Example 1).

Then, we write an Arduino code to control the LED1 and LED2 by using tasks:
• Task 1: LED1 is alternatively turned on for 2 seconds and turned off for 2 seconds.
• Task 2: LED2 is on or off by pressing the switch (pressing the switch → LED2 on;

otherwise, LED2 off).

24

ESP3234330LED1SWPin 3v3 of ESP3210KIf not press,SW is open.If press,SW is closed.16Pin GND of ESP32Long legShort leg330LED217Long legShort leg2.1 Task Management

Example 3 (Ex_Multitasking.ino)

Step 1: Create a function for Task 1.

25

2.1 Task Management

Example 3 (Ex_Multitasking.ino)

Step 1: Create a function for Task 2.

Step 2: Declare each task by
using the xTaskCreate().

26

2.1 Task Management

Example 3

A demonstration video is shown below.

27

2.2 ESP32 Dual Core

1. Show the Running Core

• The ESP32 comes with 2 Xtensa 32-bit LX6 microprocessors: core 0 and core 1. So, it

is dual core.

• When we run an Arduino code, we can monitor which core is running the current

command by using

xPortGetCoreID();

28

2.2 ESP32 Dual Core

Example 4 (Ex_ShowCore.ino)

We connect the same circuit as shown in Example 3 and modify its Arduino program in
Example 3 such that we show the running core on the serial monitor.

29

2.2 ESP32 Dual Core

Example 4 (Ex_ShowCore.ino)

Print the CPU core number.

30

2.2 ESP32 Dual Core

Example 4 (Ex_ShowCore.ino)

Print the CPU core number.

31

2.2 ESP32 Dual Core

Example 4

The result is shown on the serial monitor.

32

2.2 ESP32 Dual Core

2. Assigning a Core to a Task

As shown in 2.1 where we can assign each job to a task function. Further, we can assign
a core to each task function that we created. The steps are as follows (similar to what we
have done in 2.1).
1) We declare a task function for each job (the same way we have done in 2.1, Page 18).
In the setup() function, we have to declare each task by using the function below
2)
whose syntax is, for example,

xTaskCreatePinnedToCore( TaskName,

“TaskName”,
10000,
NULL,
1,
NULL ,
);
0

/* Task function. */
/* Task name. */
/* Stack size in bytes. */

/* Priority of the task. */
/* Task handle. */
/* Core 0*/

/* Parameter passed as input of the task */

The input parameters are similar to those in the xTaskCreate() function (on Page 19)
except the last one which we use to assign the core for this task. The number here can
be either 0 or 1 (= Core 0 or 1).

33

2.2 ESP32 Dual Core

Example 5 (Ex_AssignCore.ino)

We connect the same circuit as shown in Example 3 and modify its Arduino program in
Example 4 such that we assign Core 0 to the TimerLED task and Core 1 to the SwitchLED
task. We also show the running core on the serial monitor. Note that, unlike the previous
example where both tasks are executed by the Core 0 (concurrently), now each task is
executed by different core. Both tasks are running parallelly/simultaneously.

34

2.2 ESP32 Dual Core

Example 5 (Ex_AssignCore.ino)

35

2.2 ESP32 Dual Core

Example 5 (Ex_AssignCore.ino)

Declare the tasks and assign the cores.

36

2.2 ESP32 Dual Core

Example 5

A demonstration video is shown below.

37

Summary

Topic

2.1 Task
Management

2. ESP32
Dual Core

Detail

Command

Create a task as a function

-

Show the current running core

xPortGetCoreID();

Assigning a core to a task

xTaskCreatePinnedToCore(… );

38

3. Deep Sleep

This section consists of
3.1  ESP32 Power Modes
3.2  Deep Sleep
3.3  Timer Wake-up
3.4  Touch Wake-up
3.5  Ext0 External Wake-up
3.6  Ext1 External Wake-up

39

3.1 ESP32 Power Modes

ESP32 is a popular microcontroller used in many projects. However, ESP32 can be a
relatively power-hungry device. It usually pulls about 75mA in normal operation and hits
about 240mA while transmitting data over WiFi.

• When our IoT project is powered by a plug in the wall, we tend not to care too much
about power consumption. But if we are going to power your project by batteries,
every mA counts.

• The solution here is to cut back ESP32’s power usage by leveraging one of its Sleep
Modes. It’s really a great strategy for dramatically extending the battery life of a
project that does not need to be active all the time.

40

3.1 ESP32 Power Modes
1. Inside the Chip

In order to understand how ESP32 achieves power saving, we need to know what is inside
the chip. The following illustration shows function block diagram of ESP32 chip. At the
heart of the ESP32 chip is a Dual-Core 32-bit microprocessor along with 448 KB of
ROM, 520 KB of SRAM and 4MB of Flash memory. It also contains WiFi module,
the RTC ((Real-Time
Bluetooth Module,
Clock)) module, and lot of peripherals

the ULP (Ultra Low Power) coprocessor,

41

3.1 ESP32 Power Modes
2. Power Modes

ESP32 offers 5 configurable power modes. As per the power requirement, the chip can
switch between different power modes. The modes are: Active Mode, Modem Sleep
Mode, Light Sleep Mode, Deep Sleep Mode, Hibernation Mode.

• The normal mode is also known as Active Mode. In this mode all the features of the
chip are active. As the active mode keeps everything (especially the WiFi module, the
Processing Cores and the Bluetooth module) ON at all times, the chip requires more
than 240mA current to operate.

42

3.1 ESP32 Power Modes
2. Power Modes

•

In deep sleep mode, the CPU, most of the RAM and all the digital peripherals are
powered off. The only parts of the chip that remains powered on are: RTC controller,
RTC peripherals (including ULP co-processor), and RTC memories (slow and fast).
The chip consumes around 0.15 mA (if ULP co-processor is powered on) to 10µA.

43

3.2 Deep Sleep

1. Explanation

During deep sleep mode:
• The main CPU is powered down.
• Along with the CPU, the main memory of the chip is also disabled. So, everything

stored in that memory is wiped out and cannot be accessed.

• However, the RTC memory is kept powered on. So, its contents are preserved during

deep sleep and can be retrieved after we wake the chip up.

• So, if we want to use the data over reboot, store it into the RTC memory by defining a

global variable with RTC_DATA_ATTR attribute. For example,

RTC_DATA_ATTR  int  bootCount = 0;

•

In Deep sleep mode, power is shut off to the entire chip except RTC module. So, any
data that is not in the RTC recovery memory is lost.

• When the chip is waken up, it will restart with a reset. This means program execution

starts from the beginning once again.

44

3.2 Deep Sleep

1. Explanation

• We use this function to let ESP32 go to the deep sleep mode:

esp_deep_sleep_start();

• Note that whenever ESP32 executes this function, it will immediately go to the

deep sleep mode and does not execute any codes that are after it.

• When the chip is waken up, it will restart with a reset.

• This function can be put inside either the setup() or loop().

45

3.2 Deep Sleep

Example 6 (Ex_DeepSleep.ino)

Write this code and upload to ESP32.  Open the serial monitor to see the result. No circuit
connection is needed.

Using the deep sleep.

3.2 Deep Sleep

2. ESP32 Deep Sleep Wake-up Sources

In the previous example, the chip will be in deep sleep mode indefinitely, until external
reset is applied. However, wake up from deep sleep mode can be done using several
sources/methods. Here, we will study the following four techniques:

1) Timer

2) Touch Pin

3) Ext0 External Wake Up – Use it when you want to wake-up the chip by one particular

pin only.

4) Ext1 External Wake Up – Use it when you will use several pins for the wake-up.

47

3.2 Deep Sleep

2. ESP32 Deep Sleep Wake-up Sources

Remark:

1) Wake-up sources can be combined, in this case the chip will wake up when any one of

the sources is triggered.

2) These sources should be configured at any moment before entering in to the deep

sleep mode (i.e., before executing the esp_deep_sleep_start() function).

48

3.3 Timer Wake-Up
1. The Command

RTC controller has a built in timer which can be used to wake up the chip after a
predefined amount of time. Time is specified at microsecond precision, but the actual
resolution depends on the clock source selected. We use the following function:

esp_sleep_enable_timer_wakeup(X*1000000) ;

where X is the amount of time in the unit of seconds.

49

3.3 Timer Wake-Up

Example 7 (Ex_TimerWakeUp.ino)

We will write an Arduino program
such that ESP32 will alternatively
wake up for 10 seconds and deep
sleep for 5 seconds by using the
timer wake up.

Before

Using the deep sleep.

Declare the timer wake up.

50

3.3 Timer Wake-Up

Example 7 (Ex_TimerWakeUp.ino)

The result will be displayed in the
serial monitor as shown below. No
circuit connection is needed.

51

3.4 Touch Wake-Up

1. The Commands

You can wake up the ESP32 from deep sleep using the touch pins (touch sensors).
However, these pins must be set as interrupts. The following commands will be used for
touch wake up.
1) We need to set the touch pin that we will use to wake ESP32 as an interrupt by the

command with these 3 input parameters:

touchAttachInterrupt(Tpin, callback, Threshold);
where Tpin is the GPIO number of a touch pin, callback is the function name, and
Threshold is a value.
If the value from Tpin is lower than Threshold, the interrupt
happens and the callback function will be executed.

2) Next, we need to use the this function:

This function to set the touch pins as a wake up source.

Remark: We do not need to declare the pin mode.

esp_sleep_enable_touchpad_wakeup();

52

3.4 Touch Wake-Up

Example 8 (Ex_TouchWakeUp.ino)

We will write an Arduino program such that ESP32 will go to the deep sleep and will be
waken up when we touch the GPIO32 pin (a touch pin) by using the touch wake up. Here,
we will connect a wire to the GPIO32 pin as shown below.

53

3.4 Touch Wake-Up
Example 8

Ex_TouchWakeUp.ino

Two commands together.

Before

Using the deep sleep.

54

3.4 Touch Wake-Up

Example 8 (Ex_TouchWakeUp.ino)

A demonstration video is shown below.

55

3.5 ext0 External Wake-Up
1. The Command

• The following GPIO pins can be used as ext0 external wake up: GPIOs 0, 2, 4, 12-15,

25-27, 32-39. Note that we do not need to declare the pin mode.

• We use the following command to enable the ext0 external wake-up source and put it

before calling the esp_deep_sleep_start() function:

esp_sleep_enable_ext0_wakeup(GPIO_NUM_X, LOGIC_LEVEL);

The function takes two parameters.
✓ GPIO_NUM_X: X is the GPIO number which we will use to wake ESP32.
✓ LOGIC_LEVEL: decides if we want to trigger the wake up by a LOW or a HIGH

state of the pin.

• Example: This Arduino command:

esp_sleep_enable_ext0_wakeup(GPIO_NUM_32, LOW);
means that “when the voltage across the pin 32 is LOW, the ESP32 will wake up.”

56

3.5 ext0 External Wake-Up

Example 9 (Ex_ext0WakeUp.ino)

We connect a switch to the GPIO32 as shown below and write an Arduino program to
wake ESP32 from deep sleep by pressing the switch.

57

ESP3232SWPin 3v3 of ESP3210KIf not press,SW is open.If press,SW is closed.Pin GND of ESP323.5 ext0 External Wake-Up

Example 9 (Ex_ext0WakeUp.ino)

Using the Ext0 wake-up.

Before

Using the deep sleep.

58

3.5 ext0 External Wake-Up

Example 9 (Ex_ext0WakeUp.ino)

A demonstration video is shown below.

59

3.6 ext1 External Wake-Up
1. The Command

• The ext1 external wake up is for the cases that we would like to have many pins to

wake ESP32 up. There are two options:
1) One of these pins can wake ESP32 up.
2) All of these together (= AND logic) will wake ESP32 up.

60

3.6 ext1 External Wake-Up
1. The Commands

• The following GPIO pins can be used as ext1 external wake up: GPIOs 0, 2, 4, 12-15,

25-27, 32-39. Note that we do not need to declare the pin mode.

• We use the following command to enable the ext1 external wake-up source and put it

before calling the esp_deep_sleep_start() function:

esp_sleep_enable_ext1_wakeup(BUTTON_PIN_MASK, LOGIC_LEVEL);

The function takes two parameters.
✓ BUTTON_PIN_MASK: we use to specify which pins will be used.
✓ LOGIC_LEVEL: specifies which option that we will use to wake ESP32 up.

61

3.6 ext1 External Wake-Up
1. The Commands

• The BUTTON_PIN_MASK parameter is to identify which pins will be used. It can be
written as a Hex number. The GPIO pins can be mapped to 40 bits as shown below.

• The MSB bit is for GPIO39. The LSB bit is for GPIO0.
• Bit masked with 1 to specify its usage in the ext1 external wake up.
• Above, if we want to use GPIO32 and GPIO33, the BUTTON_PIN_MASK will be

set to 0x0300000000.

62

3.6 ext1 External Wake-Up
1. The Commands

• The LOGIC_LEVEL parameter specifies which option that we will use to wake ESP32

up.
• If the LOGIC_LEVEL parameter is ESP_EXT1_WAKEUP_ANY_HIGH, we will

wake ESP32 up if one of the selected pins is high.

✓ Example: If the BUTTON_PIN_MASK is set
voltage at either pin 32 or 33 will wake ESP32.

to 0x0300000000,

the high

• If the LOGIC_LEVEL parameter is ESP_EXT1_WAKEUP_ALL_LOW, we will wake

ESP32 up if all the selected pins are low.

✓ Example: If the BUTTON_PIN_MASK is set to 0x0300000000, the low

voltages at both pin 32 and 33 will wake ESP32.

63

3.6 ext1 External Wake-Up

Example 10 (Ex_ext1WakeUp.ino)

We connect two switches to the GPIO02 and GPIO32 as shown below and write an
Arduino program to wake ESP32 from deep sleep by pressing one of these switches. Note
that, by connecting the switches in this way, pressing the switch gives the HIGH logic at
the ESP32 pin. Since we will use GPIO2 and GPIO32 for ext1 wake up,
the
BUTTON_PIN_MASK parameter will be set to 0x0100000004.

64

ESP322SW1330If not press,SW is open.If press,SW is closed.Pin GND of ESP3232SW2Pin 3v3 of ESP3210K10K3303.6 ext1 External Wake-Up

Example 10 (Ex_ext1WakeUp.ino)

Using the Ext1 wake-up.

Before

Using the deep sleep.

65

3.6 ext1 External Wake-Up

Example 10 (Ex_ext1WakeUp.ino)

A demonstration video is shown below.

66

Summary

Topic

Detail

Command

3.2 Deep Sleep

Go to deep sleep

esp_deep_sleep_start();

3.3 Timer Wake-
Up

Wake ESP32 by
using a timer

esp_sleep_enable_timer_wakeup(X*1000000) ;

3.4 Touch Wake-
Up

Wake ESP32 by
using a Touch pin

3.5 ext0 External
Wake-Up

Wake ESP32 by
using a pin

touchAttachInterrupt(Tpin, callback, Threshold);

esp_sleep_enable_touchpad_wakeup();
esp_sleep_enable_ext0_wakeup(GPIO_NUM_X,
LOGIC_LEVEL);

3.6 ext1 External
Wake-Up

Wake ESP32 by
using a set of pins

esp_sleep_enable_ext1_wakeup(BUTTON_PIN_
MASK, LOGIC_LEVEL);

67

4. Advanced Topics

68

4. Advanced Topics

1) ESP32 Flash Memory – Store Permanent Data (Write and Read):

https://randomnerdtutorials.com/esp32-flash-memory/

2) ESP32 Over-the-air (OTA) Programming – Web Updater Arduino IDE:
https://randomnerdtutorials.com/esp32-over-the-air-ota-programming/

3) Get Epoch/Unix Time with the ESP32:

https://randomnerdtutorials.com/epoch-unix-time-esp32-arduino/

4) Etc.

69

Questions?

70


