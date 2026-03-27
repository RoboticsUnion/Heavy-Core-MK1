# Software

This folder contains the software stack for controlling a robotic arm, including UI, control logic, and embedded firmware. 

Our Software consists of three parts:
    - RoboticsUnion Control GUI
    - RoboticsUnion Robot Control
    - RoboticsUnion Firmware

# RoboticsUnion Control GUI

The RoboticsUnion Control GUI is the highest layer of control in our software. 
It can be run on any Windows PC that is connected to a robot via LAN.

The Conrol GUI shows important data from the robot's sensors and is able to transmit data to the robot. This way you can control a connected robot.

Written in C++.

# RoboticsUnion Robot Control

The RoboticsUnion Robot Control software is the second highest layer of control and the core component of our software.

This component runs on a small PC near our robotic arm and does all the computation requiered for movement and task execution.

It also serves as a link between the Firmware and the RoboticsUnion Control GUI by translating high-level commands into low-level hardware instructions.

Written in Python.

# RoboticsUnion Firmware

The RoboticsUnion Firmware is the lowest layer of control and and runs directly on the MCUs that control the hardware of the robot.

Written in C++.
    
