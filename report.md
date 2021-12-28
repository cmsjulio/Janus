# Hardware Overview

The robot manufacturing was divided in four parts: chassis and motors, ultrasonic obstacle avoidance, infrared beacon detection, and controller.

For the chassis, two 9V DC motors were used in the back wheels of the robot that were connected with the front wheels using a caterpillar device. It was built using Lego pieces but merely because those were available at low cost. There are many different chassis available online and most of them would fit for this project as well.

Three HC-SR04 ultrasonic sensors were used to detect frontal, right and left obstacles, being separated at 90 degree intervals.

For the beacon detection, two TSOP38238 IR receivers were used and placed one next to the other, with a black pasteboard in between to refrain IR signals. The robot was configured to read and respond only to the Sony TV power signal 0xa90, but that could be changed. The robot could be further configured to respond differently to different signals. One could install a beacon emitter with a signal X in a certain place and another beacon with a signal Y in another place and then have the robot to move to each place only by changing which signal it is pursuing.

An infrared 950nm LED was used as the beacon emitter. An Arduino Uno board was used to generate the 0xa90 signal as well as a 330 ohms resistor was necessary to reduce the current through the LED.
