CSS452 Internet of Things

Homework 2: ESP32 – Multitasking and Deep Sleep

1.  Do the Example 5 in Lecture Note 4.  Take a video to show

•  circuit connection,
•  Arduino code,
•  demonstration:

o  The serial monitor shows which core is running.
o  LED1 is alternatively turned on for 2 seconds and turned off for 2 seconds.
o  LED2 is on if we press the switch “SW”; otherwise, LED2 is off.

Name your video as “P1” and submit to the Google Classroom.

2.  Do the Example 9 in Lecture Note 4.  Take a video to show

•  circuit connection,
•  Arduino code,
•  demonstration:

o  The serial monitor shows that ESP32 is in the deep sleep.
o  Pressing the switch (SW) wakes ESP32 up (take a video to show “pressing the switch”

and, then, the serial monitor shows that ESP32 wakes up).

Name your video as “P2” and submit to the Google Classroom.

3.  In this problem, we will revise Example 5 in Lecture Note 4 by connect one more switch (call

it “SW1”) to ESP32 (to the pin GPIO26) as shown below.

ESP3234330LED1SWPin 3v3 of ESP3210K16Pin GND of ESP32Long legShort leg330LED217Long legShort legSW110K26

Write the Arduino code such that

•  when ESP32 is on (similar to the jobs in Example 5 in Lecture Note 4):

o  The serial monitor shows which core is running.
o  LED1 is alternatively turned on for 2 seconds and turned off for 2 seconds.
o  LED2 is on if we press the switch “SW”; otherwise, LED2 is off.

•

•

 (New) when ESP32 is on, pressing the switch “SW1” will let the ESP32 go to deep sleep.
Here, we use the pin-change interrupt to do this (similar to Example 2 in Lecture Note 4).
(New) After ESP32 is in deep sleep, it will wake up 15 seconds later by using the timer
wakeup (similar to Example 7 in Lecture Note 4).

Take a video to show

•  circuit connection,
•  Arduino code,
•  demonstration of the above tasks.

Name your video as “P3” and submit to the Google Classroom. The demonstration video is
shown in the attached file.


