# TrackingRobot
Code for a robot that tracks humans.

This is an ongoing project.

The idea is to capture input from a camera using a laptop or raspberry pi.
Then send the xy coordinates of a detected human to an arduino using UART or Serial communication.
The arduino will control two servos that will position the camera to face the human.

Eventually the robot will have mobility and be able to follow humans around.

At first I was going to use Python and PySerial, but the serial communication was too slow.
So I switched to using C++ and wjwwood's Cross-Platform, Serial Port Library.
The serial communication is much faster now.
