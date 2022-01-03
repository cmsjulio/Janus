# Hardware Overview

The robot manufacturing was divided in four parts: chassis and motors, ultrasonic obstacle avoidance, infrared beacon detection, and controller.

For the chassis, two 9V DC motors were used in the back wheels of the robot that were connected with the front wheels using a caterpillar device. It was built using Lego pieces but merely because those were available at low cost. There are many different chassis available online and most of them would fit for this project as well.

Three HC-SR04 ultrasonic sensors were used to detect frontal, right and left obstacles, being separated at 90 degree intervals.

For the beacon detection, two TSOP38238 IR receivers were used and placed one next to the other, with a black pasteboard in between to bar IR signals. The robot was configured to read and respond only to the Sony TV power signal 0xa90, but that could be changed. The robot could be further configured to respond differently to different signals. One could install a beacon emitter with a signal X in a certain place and another beacon with a signal Y in another place and then have the robot to move to each place only by changing which signal it is pursuing.

An infrared 950nm LED was used as the beacon emitter. An Arduino Uno board was used to generate the 0xa90 signal as well as a 330 ohms resistor was necessary to reduce the current through the LED.

The controller was built using an Arduino Uno board with an Adafruit v2.3 Motor Shield. The motor shield was added for the sake of simplicity; although it could have been possible and cheaper to use an H bridge or relays. The shield stacking headers did not come with the motors and had to be bought separately. For more information on how to set up the Adafruit shield, check the Adrafuit website at https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/install-headers.

A PCB board was also used, along with different wires and jumpers. Also, two 9V batteries were used to power the robot and the beacon system separately. A list with all components that were purchased for this project and its respective prices [is shown below](https://imgur.com/I4Ofgb9).

![img1-list](https://user-images.githubusercontent.com/88581731/147907440-575f9a7b-2dd5-4b92-98a3-f69b6e8670f2.png)


[In this other picture that follows below](https://imgur.com/X8Xc0yz) are shown the chassis, the Arduino UNO Board, one of the TSOP38238 IR receivers, one of the HC-SR04 Ultrasonic sensors, the IR LED with its 330 ohms resistor soldered together and the Adafruit Shield for Arduino V2.3.

![img2-chassis](https://user-images.githubusercontent.com/88581731/147907580-a6abd4b8-6569-4b3e-ae90-19879b9287b0.png)


# Manufacturing

After all the necessary components were gathered, the manufacturing process started. First, three HC-SR04 ultrasonic and two TSOP38238 IR sensors were soldered in the PCB, [as shown below](https://imgur.com/X0lLg2k) (note that the two IR that appears in the frontal corners are not functional for this project).

![img3-soldering](https://user-images.githubusercontent.com/88581731/147907688-1c3a343d-e31f-4828-aad6-299a4f94b1a2.png)


The connections for these components are as shown in the tables below:

For the ultrasonic sensors, [see this table](https://imgur.com/Pf8tcSk).

![img4-table1](https://user-images.githubusercontent.com/88581731/147907838-990503ab-e1fc-414c-8730-4b491761c6e4.png)


For the IR sensors, [see this table](https://imgur.com/6dycmWJ).

![img5-table2](https://user-images.githubusercontent.com/88581731/147907863-661a06ad-8895-4fda-a127-11b2838faec2.png)


Each component is soldered on its position and jumpers are soldered to connect common pins to common trails – all the pins that are connected to Arduino ground pin, for example, are linked to a common trail through a jumper, so that later only one connection between PCB and Arduino is necessary to link all of such pins to the Arduino ground pin. For the IR sensors, check the datasheet of the TSOP38238 to find the position of pins OUT, GND and Vs – available at http://www.vishay.com/docs/82491/tsop382.pdf. The GND, ECHO, TRIG and VCC pins of the HC-SR04 sensor are displayed but in case of need, its datasheet can be found at http://www.micropik.com/PDF/HCSR04.pdf.

Next, the PCB was fixed on top of the chassis – one could use duct tape. Then, the assembled Arduino board plus the motor shield is placed on top of it, so that the connections between Arduino and PCB can be made – see tables above. The right motor goes in the M1 port of the Adafruit shield, the left motor goes in the M2 port. With the 9V battery also attached and connected to the power input of the Adafruit motor shield, the robot manufacturing is all set, and the only pendency regards the upload of the code to the Arduino controller and setting the beacon.

Note: Do not plug in the Adafruit motor shield jumper. Instead, connect the Arduino to a computer with the IDE via USB to upload the controller code. The jumper should not be plugged while the Arduino is connected via USB.

For the beacon, the manufacturing is much simpler as shown in the image below. One pin of a 330 ohms resistor is connected to the anode pin of the IR LED – the anode pin can be identified by the longer leg – and the other one to the Arduino pin #3. The cathode pin of the IR LED is connected to ground. An external battery feeds the Arduino – positive was connected to “Vin” and negative to ground.

Note that you cannot see whether the IR LED is working or not, as it is emitting IR, a non-visible light wave. Most cameras presently are equipped with filters, and that might be the reason why [the picture below](https://imgur.com/FrY0jTd) does not show any sign of functionality, even though the code was already uploaded when it was taken. 

![img6-beacon](https://user-images.githubusercontent.com/88581731/147907986-f729b703-0456-4c24-b975-0992e4afb188.png)


With the beacon system set, uploading the codes for each Arduino is all that is left.


# Uploading the Code for the Robot

An Arduino was responsible for controlling the robot. The code was developed with the help of three external libraries. Directions on how to install the libraries needed are available in Appendix A. The code for controlling the robot is available in Appendix B. The idea behind the code can be summarized with the pseudo code, [as follows](https://imgur.com/KV2YVNj):

![img7-pcode](https://user-images.githubusercontent.com/88581731/147908064-e5c99032-e21b-4bb9-95ef-36e285971251.png)


The first priority of the robot’s code will be to avoid a detected frontal obstacle within the distance of LIMIT. According to the code in Appendix B, such distance was set at 30cm. If that is the condition, it goes through the obstacle avoidance maneuver, using the right and left ultrasonic sensors to decide where to turn. If the right distance detected is greater than the left distance, it turns right; otherwise it turns left.

When it is the case that no frontal obstacle is detected, the robot will then check for the readings on the infrared sensors. If a signal is detected on the right IR sensor only, the robot will then turn right. If a signal is detected on the left IR sensor only, the robot will then turn left. If a signal is detected on both sides, or no signal detected at all, the robot will go forward.

To upload the code to the Arduino, connect it to a computer with the Arduino IDE software and libraries listed on Appendix A installed, then copy and paste the code shown in Appendix B and hit upload.

Notice that right after the code was uploaded; the robot motors might instantly start. The robot will proceed as specified previously with the help of the pseudo code, and since the beacon is not sending any signal yet, the robot will wander and avoid collisions.

If the robot is moving, but not exactly as explained in the pseudo code, place it in a position where there is no frontal obstacle within 30cm and observe in what direction it is turning. If it is turning right, change the wire positions of the M1 connection on Adafruit motor controller shield. If it’s turning left, change the wire positions of the M2 connection.


# Uploading the Code for the Beacon

The code for the beacon is available in Appendix C. It was developed with the help of the IRremote library. Instructions on how to install the libraries needed for this project can be found in Appendix A. The code makes the beacon send the Sony TV power signal continuously so that the robot can track it.

To upload the code to the Arduino, connect it to a computer with the Arduino IDE software and libraries listed on Appendix A installed, then copy and paste the code shown in Appendix C and hit upload.

After the code was uploaded, the beacon is ready to be tracked by the IR receivers in the robot. Note regarding the pseudo code, that even when the robot is receiving signal on both IR receivers, the robot goes forward. That means the robot might get to the beacon, but it will not stop once it has reached the beacon – as the controller cannot calculate the distance between IR receiver and IR source. Further, other sensors could be attached to the robot in order to solve this matter.


# Discussion

The robot responds very well to the given task of tracking the IR signal. The obstacle avoidance routine, surprisingly very simple, is functional and the fact that it works fully autonomously adds even more value to its success. Nevertheless, there is still room for improvement. The ultrasonic sensors did not have to necessarily be displaced at a 90 degree interval. A shorter angle would make it possible for the robot to detect frontal obstacles with a wider range and with no down sides. There is also the option for the robot to have one single ultrasonic sensor attached to a servo motor, functioning similar to a radar. This would decrease the cost of two sensors at the expense of one servomotor.  Such a design would make room for more possibilities in detecting objects. The robot would not be constrained to only three directions to which it could send and get ultrasonic signals. The design for the IR sensing system could surely be improved. A proper nest for the two sensors could be developed; one that would not only divide the two halves of the robot for IR sensing but also block signals that would come from behind the robot. It could also, if not sensing any obstacle or IR signal, turn to the opposite direction as if in an attempt to get something. The caterpillar wheels are good for unstable grounds and work very well when the motors are properly powered. As soon as the batteries lose some of their charge, the high friction of the robot makes the turning movement of the robot a lot more difficult. As home activities are the focus of this project, the benefits of the caterpillar wheels are not appealing to the point of neglecting their down sides. Caster wheels could possibly be an improvement for the general housing environments for which project Janus is firstly designed.

There would also be the possibility of improving the robots ability to adapt to the environment. For example, an ultrasonic sensor could be placed in the robot facing upward.  This could allow for the robot to be aware of the vertical operating space. That is not the ideal solution for the future, but could be functional more easily integrated in the short term.

As to its intelligence, it is still one of a simple reflex agent.  Given its sensors, there are not too many more options available. With the right set of precise actuators, it would be possible for the robot to keep track of its path as it travels.  It is already possible currently, but not to the point where one can trust that there will be no significant error accumulation. Allowing for the robot to store its current state and use this information to create a model for the environment could then be used as a parameter for future decisions.




