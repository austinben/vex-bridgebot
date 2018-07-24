# vex-bridgebot

Showcase of code written to run an autonomous robot using a VEX Robotics kit. 

## Backround

As a first year engineering project, students at the University of Victoria were asked to design and build a prototype autonomous robot using a VEX Robotics kit. The robot was meant to be a prototype of a possible underwater cable connecting robot that would be used by [Ocean Networks Canada](http://www.oceannetworks.ca/).

## The robot

The prototype was meant to be a proof of concept for beacon location and cable connection. It was placed in a 3x3 meter arena facing away from a target beacon. The robot would then - without any intervention - have to locate the beacon, move toward it, attach a cable (or similar mechanism), and detach itself from the cable and back away from the beacon without disturbing the cable it had previously attached.

Our team built a wide, tall robot that simply positioned itself directley above the beacon. We called this robot the bridgebot, as it somewhat resembeled a bridge.


## Code

The programming of the robot was done entirely through the [RobotC](http://www.robotc.net/) IDE. This IDE is specifically designed for creating programs for the VEX Robotics kits. 

We were strongly encouraged to use a switch-case implementation and develop a finite state machine to guide our robot's actions.

The robot followed a simple FSM throughout all of its actions. To start, the robot would rotate slowly clockwise untill its phototransistor detected the IR light from the beacon. Next, it would drive towards the beacon untill the switch on the underside was bumped. The robot would then start its connection process of dropping a weighted cable end ontop of the beacon, then back away slowly.

