Lecture Note 6:
ESP32 – MQTT Clients

CSS452 Internet of Things

Dr. Seksan Laitrakun
School of ICT, SIIT, Thammasat University

1

Outlines

1.

2.

Introduction to MQTT

Installing a Necessary Library in Arduino IDE

3. Publishing/Subscribing via a Public MQTT Broker using Two ESP32

4. Publishing/Subscribing via a Public MQTT Broker using One ESP32

2

References

• Random Nerd Tutorials: https://randomnerdtutorials.com/projects-esp32/
• HiveMQ: https://www.hivemq.com/developers/

3

1. Introduction to MQTT

4

MQTT and Publish/Subscribe Method

• MQTT (Message Queuing Telemetry Transport) is a communication protocol for the
Internet of Things (IoT) that uses the publish/subscribe method for communication.

It is a popular for IoT systems (which is a network of constrained devices).

• MQTT is lightweight and is used in low bandwidth environments.
•
• Three main components in MQTT:
✓ Publisher/Producer (sender),
✓ Broker (middleman)
✓ Subscriber/Consumer (receiver).

5

MQTT and Publish/Subscribe Method

Publish/subscribe method:
1) The producer publishes a message (data) and the topic to the Broker.
2) The Broker receives the message (data) and the topic.
3) The Broker sends the message (data) to the appropriate consumer(s) that are

subscribed to this topic.

6

Advantages of MQTT

The publish/subscribe method (also known as pub/sub) provides an alternative to
traditional client-server architecture.
• HTTP protocol: In the client-sever model, a client communicates directly with an end

point.

• Advantages: The pub/sub model decouples the client that sends a message (the

publisher) from the client or clients that receive the messages (the subscribers).
• The publishers and subscribers never contact each other directly. In fact, they are not
even aware that the other exists. Unlike using the HTTP protocol (Lecture note 6),
the publisher and subscriber do not need to know the IP addresses of each other.

• The connection between them is handled by a third component (the broker). The job
of the broker is to filter all incoming messages and distribute them correctly to
subscribers.

• The topic is the key such that the message can be delivered to the corresponding

subscribers.

• As a result, the publisher and subscriber do not know each other.

7

How does MQTT work?

• The publish/subscribe method solves the problem of detail, by introducing a new

concept, i.e., a topic.
1) Each publisher must declare itself to the MQTT broker and its published topics.
2) Each subscriber must declare itself as a subscriber and its subscribed topics.
3) The MQTT broker will distribute messages from publishers to subscribers

according to the topic.

•

In MQTT, an IoT device can be
• a publisher,
• a subscriber,
• both publisher and subscriber.

8

Example

9

Topic Setup: A Systematic Way

Systematically, a topic can be defined as a hierarchy (or level), using a slash (/) as a
separator.
• For example, a smart home (called “Home1”) consists 3 rooms: Room1, Room2,
Room3. Each room consists to 2 sensor nodes: temperature node (called “temp”) and
humidity node (called “humid”). Totally, we will have 6 sensor nodes to send these
data. These sensor nodes might be set up as publishers and their topics could be
• Home1/Room1/temp
• Home1/Room1/humid
• Home1/Room2/temp
• Home1/Room2/humid
• Home1/Room3/temp
• Home1/Room3/humid
We have 3 topic levels (we can create as many levels as we want).
• A device who want the data from the humidity data from room 2 will subscribe the

topic named “Home1/Room2/humid”.

10

Topic Setup: A Systematic Way

By setting the topics in this way (hierarchy), we can use two wild cards when a devices
would like to subscribe from many topics.
1) The single-level wildcard, indicated by a plus sign (+), can be used to subscribe to

various topics at once, but only one level deep.

Example:

Given the following published topics:
• Home1/Room1/temp
• Home1/Room1/humid
• Home1/Room2/temp
• Home1/Room2/humid
• Home1/Room3/temp
• Home1/Room3/humid

a) Which topics will a subscriber receive if

it subscribes to Home1/Room1/+?

b) Which topics will a subscriber receive if

it subscribes to Home1/+/temp?

11

Topic Setup: A Systematic Way

2) Multi-level wildcards, indicated by a number/hashtag character (#), can be used to
subscribe to various topics at once – as the name suggests – multiple levels deep.

Example:

Given the following published topics:
• Home1/Room1/temp
• Home1/Room1/humid
• Home1/Room2/temp
• Home1/Room2/humid
• Home1/Room3/temp
• Home1/Room3/humid

a) Which topics will a subscriber receive if

it subscribes to Home1/Room1/#?

b) Which topics will a subscriber receive if

it subscribes to Home1/#?

12

Quality of Service

• What is QoS? A setting that defines the guarantee of message delivery between the

client and the broker.

• Who decides? The publisher sets the level for the message, and the subscriber sets the

maximum level it is willing to receive.

• The Rule: The message is always delivered at the lower of the two QoS levels.

Level

Guarantee

Description

QoS 0 Fire and Forget At most

once

The message is sent once with no
confirmation. Fast but unreliable.

QoS 1 Acknowledged
Delivery

At least
once

QoS 2 Assured
Delivery

Exactly
once

The message is guaranteed to arrive, but
duplicates may occur if acknowledgments are
lost.

The message is guaranteed to arrive exactly
one time through a multi-step handshake.
Slowest but most reliable.

13

2. Installing a Necessary Library in

Arduino IDE

14

Installing a Necessary Library in Arduino IDE

To let an ESP32 to sent a message by using the MQTT protocol, we must install a
library “PubSubClient.h” in the Arduino IDE.
1) On the Arduino IDE, choose

Sketch → Include Library → Manage Libraries…

2) Search for PubSubClient and install it. (This library is provided by Nick O’Leary.)

3) After finishing, you close the Arduino IDE and open it again.

15

3. Publishing/Subscribing via a Public

MQTT Broker using Two ESP32

16

3.1 Project Outline

In this project, we will use two ESP32.
a) We connect an ESP32 (called “PubNode”) to a potentiometer and set it as a publisher
to send the potentiometer value to the other ESP32 (subscriber) via a public MQTT
broker.

b) We connect an ESP32 (called “SubNode”) to an LED and a resistor and set it as a

subscriber to receive the potentiometer value via a public MQTT broker.

Rotating the potentiometer on the PubNode will turn on/off the LED on the SubNode:

•

If the potentiometer is more than 500, the LED will be on; otherwise, the LED will
be off.

These two ESP32 do not need to connect to the same access point
and they can be at different locations.

17

3.1 Project Outline

A demonstration video is shown below.

18

3.1 Project Outline

Here is a list of public MQTT brokers which are
free (https://mntolia.com/10-free-public-private-
where
mqtt-brokers-for-testing-prototyping/),
the broker address and port are specified. In this
project, we will use the HiveMQ as our public
MQTT broker (port 1883).
• Note that if there is a problem with HiveMQ,

you might choose Mosquitto instead.

19

3.2 Schematic

• We connect a potentiometer to the PubNode as shown below.
• We connect an LED and a resistor to the SubNode as shown below.

20

ESP32(PubNode)A0PotentiometerPin 3v3 of ESP32Pin GND of ESP32ESP32(SubNode)Pin GND of ESP32330LED263.3 Arduino Code

In this project, we have two Arduino codes.
1) The Arduino code for the PubNode: “Public_HiveMQ_PubNode.ino”. Using this
code will set the ESP32 to be a publisher, read the potentiometer value, and send it to
the public HiveMQ broker.

2) The Arduino code for the SubNode: “Public_HiveMQ_SubNode.ino”. Using this
code will set the ESP32 to be a subscriber, receive the subscribed message from the
public HiveMQ broker, and turn on/off the LED.

21

3.3 Arduino Code

In this code, we will demonstrate how to:
1) Configure the ESP32 as an MQTT Client

•

Set up the connection and define its role as either a Publisher or a Subscriber.

2) Publish Sensor Data

• Read a value from a potentiometer and send it to a specific MQTT topic.

3) Subscribe and Act on Data

• Listen for messages on a topic and use the received data to control a physical

output (an LED).

22

3.3 Arduino Code

Please revise the given two codes as follows.
1) Write this code in your Arduino IDE.
2) You have to fill in your SSID and Password of your access point.

3) Add your student ID at the end of Client and Topic such that we have unique names.

3.1) *ClentID: PubNode and SubNode have different ClientIDs and different from

other students.

3.2) *Topic: The topic must be the same topic name in both PubNode and SubNode.

However, it must be a different name from other students.

23

3.3.1 Arduino Code: “Public_HiveMQ_PubNode.ino”

Necessary libraries

WiFi access point parameters

The MQTT parameters

Set up an MQTT node

24

3.3.1 Arduino Code: “Public_HiveMQ_PubNode.ino”

To connect to your WiFi access point.

Specify the MQTT broker and
connect to it.

25

3.3.1 Arduino Code: “Public_HiveMQ_PubNode.ino”

To check the connection to the
MQTT broker.

This part is as a publisher.
• Check every 2 seconds.
• Publish the value from the pin A0
to the MQTT broker under the
topic “Topic”.

• The dtostrf() is a function to
convert an integer to a string.

• The .publish() is to publish.

26

3.3.1 Arduino Code: “Public_HiveMQ_PubNode.ino”

A custom function to connect to the
MQTT broker and listen to an incoming
message from the broker.

Compare to the Arduino code on Page
23, there is no the .setCallback() method
and the .subscribe() method because this
ESP32 is working as a publisher only.

27

3.3.2 Arduino Code: “Public_HiveMQ_SubNode.ino”

Necessary libraries

WiFi access point parameters

The MQTT parameters

Set up an MQTT node

28

3.3.2 Arduino Code: “Public_HiveMQ_SubNode.ino”

To connect to your WiFi access point.

Specify the MQTT broker, set up the
call back (for a subscriber), and
connect to it.

29

3.3.2 Arduino Code: “Public_HiveMQ_SubNode.ino”

To check the connection to the
MQTT broker.

This is for a subscriber. This command
should be called regularly to allow the
client to process incoming messages and
maintain its connection to the server.

A custom function:
•
•

to connect to the MQTT broker
(as a subscriber) listen to an incoming
message from the broker.

30

3.3.2 Arduino Code: “Public_HiveMQ_SubNode.ino”

This function will be called if the ESP32 receives an
incoming message from the broker.

The incoming message is stored in the variable
“ValString”.

• Convert the ValString to an integer.
• Store it in the variable “ValInt”.
• Use the ValInt to turn on/off the LED.

31

3.4 Code Explanation

The important parts of the code can be explained as follows.
1) Declare MQTT parameters: MQTT broker address, MQTT port number (in general, it

is 1883), name of the MQTT publisher or subscriber, and the topic.
• The publisher name, subscriber name, or Topic can be any name.

• Pub Node:

• Sub Node:

2) Set the ESP32 as a web client and pub/sub client.

32

3.4 Code Explanation

3) Set up the MQTT protocol.

• Specify the MQTT server.
• Specify that if a subscribed message arrives, call the function “callback”.
• Connect to the MQTT broker using a custom function “ConnectMQTT();”.

• Pub Node:

• Sub Node:

4) Check whether the ESP32 connects to the MQTT broker.

Pub Node:

Sub Node:

33

3.4 Code Explanation

5)

In the Sub Node, call this function regularly to allow the client to process incoming
messages and maintain its connection to the server.

6)

In the Pub Node, convert an integer to a string and publish (send) it under the topic
“Topic” to the MQTT broker.

34

3.4 Code Explanation

7)

In the Sub Node, the topic to be subscribed from the MQTT broker.

8)

In the Sub Node, the function “callback” will be called when a subscribed message is
received. The subscribed message is stored in the pointer variable “payload” whose
length is equal to the variable “length”.

9)

In the Sub Node, retrieve the subscribed message from the pointer variable “payload”
to the variable “ValString”.

35

4. Publishing/Subscribing via a Public
MQTT Broker using One ESP32

36

4.1 Project Outline

In this project, we will implement a global MQTT-based system, where
• a public MQTT broker will be set up as our MQTT broker,
• our ESP32 will work as both publisher and subscriber (to send the data to itself).

37

4.1 Project Outline

A video demonstration is shown below.

38

4.1 Project Outline

Here is a list of public MQTT brokers which are
free (https://mntolia.com/10-free-public-private-
where
mqtt-brokers-for-testing-prototyping/),
the broker address and port are specified. In this
project, we will use the HiveMQ as our public
MQTT broker (port 1883).
• Note that if there is a problem with HiveMQ,

you might choose Mosquitto instead.

39

4.1 Project Outline

In this project, we will have the following tasks.
1) We will connect a potentiometer and an LED (and a resistor) on the ESP32.
2) Rotating the potentiometer will turn on and off the LED.

• Potentiometer value > 500 → LED is on
• Otherwise → LED is off.

3) Roles of ESP32:

• As a publisher, ESP32 will send the potentiometer value to the MQTT broker every 2 seconds.
• As a subscriber, ESP32 will receive a message (potentiometer value) from the MQTT broker
(when the broker receives a new value). ESP32 compares the received value (> 500 or not) and
turns the LED on or off, accordingly.

40

4.2 Schematic

We connect a potentiometer and an LED to the ESP32 as shown in the following
schematic diagram.

41

ESP32A0PotentiometerPin 3v3 of ESP32Pin GND of ESP32330LED264.3 Arduino Code

The Arduino code “Public_HiveMQ_PubSub.ino” will set the ESP32 to be both publisher
(sends the potentiometer value to the broker) and subscriber (receives the potentiometer
value from the broker) and connect to the HiveMQ broker. Please revise the given code as
follows.
1) Write this code in your Arduino IDE.
2) You have to fill in your SSID and Password of your access point.

3) Add your student ID at the end of Client and Topic such that we have unique names.

42

4.3 Arduino Code

Necessary libraries

WiFi access point name and password

MQTT Details

Set up an MQTT node

43

4.3 Arduino Code

To connect to your WiFi access point.

• To specify the MQTT broker.
• To set up the callback from the MQTT

broker.
• The callback function is called

when new messages arrive at the
client.

• To connect to the MQTT broker.

44

4.3 Arduino Code

To check the connection to the MQTT
broker.

This is for a subscriber. This command
should be called regularly to allow the
client to process incoming messages and
maintain its connection to the server.

This part is as a publisher.
• Check every 2 seconds.
• Publish the value from the pin A0
to the MQTT broker under the
topic “Topic”.

• The dtostrf() is a function to
convert an integer to a string.

• The .publish() is to publish.

45

4.3 Arduino Code

A custom function:
•
•

to connect to the MQTT broker,
listen to an incoming message from
the broker.

46

4.3 Arduino Code

This function will be called if the ESP32 receives an
incoming message from the broker.

The incoming message is stored in the variable
“ValString”.

• Convert the ValString to an integer.
• Store it in the variable “ValInt”.
• Use the ValInt to turn on/off the LED.

47

4.4 Code Explanation

The important parts of the code can be explained as follows.
1) Declare MQTT parameters: MQTT broker address, MQTT port number (in general, it

is 1883), name of the MQTT publisher or subscriber, and the topic.
• The publisher name, subscriber name, or Topic can be any name.

2) Set the ESP32 as a web client and pub/sub client.

48

4.4 Code Explanation

3) Set up the MQTT protocol.

• Specify the MQTT server.
• Specify that if a subscribed message arrives, call the function “callback”.
• Connect to the MQTT broker using a custom function “ConnectMQTT();”.

4) Check whether the ESP32 connects to the MQTT broker.

5) Call this function regularly to allow the client to process incoming messages and

maintain its connection to the server.

49

4.4 Code Explanation

6) Convert an integer to a string and publish (send) it under the topic “Topic” to the

MQTT broker.

7) Declare the topic to be subscribed from the MQTT broker.

8) The function “callback” will be called when a subscribed message is received. The
subscribed message is store in the pointer variable “payload” whose length is equal to
the variable “length”.

50

4.4 Code Explanation

9) Retrieve the subscribed message from the pointer variable “payload” to the variable

“ValString”.

51

Questions?

52


