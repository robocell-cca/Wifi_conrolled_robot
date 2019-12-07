# Wifi controlled robot 

This file contrains a .ino file which can be uloaded to microcontrollers like ESP8266 etc.It contains for the code of a semi-autonomous robot. It is different from an autonomous robot aas in that it requires explicit user input for its function but executes the action correponding to the input autonomously. This robot is controlled using communication over Wifi using the Microcontroller in Access point mode, using an android app.

# Basic funtioning of the robot:

1. When the code is run, ESP8266 sets up a local server, with its root page as /, with specified IP address and port

2. then  the microcontrolller sets up itself as an Access point using the specified IP address

3.  A function named handleClient() is run wich constantly checks whether the connected device has sent anything or not.

4. If a device was connected and it sent data, which is in the form of characters 'F','B','L','R','S' which denote the instruction for the robot to move forward, backward, left, right or stop respectively.
 
 
