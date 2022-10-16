# EEE3097S Design Project

## Welcome
Welcome to our EEE3097S design project. This project is proudly designed by Natasha Soldin and Rory Schram.

## Introduction
The following project design is for an ARM based digital IP using an STM32F051-microcontroller. This design aims to retrieve, compress and encrypt data from an Inertial Measurement Unit (IMU) sensor. This type of sensor includes an Accelerometer, a Gyroscope, a Magnetometer and a Barometer. This design will be implemented as a buoy installed on an ice 'pancake' in the Southern Ocean to collect data about the ice and wave dynamics.

This data will then be transmitted using the Iridium communication network, which is a global satellite communications network. However, this is extremely costly and therefore the data would need to be compressed to reduce its size. The data is also encrypted for security purposes. 

## Repository Contents:
- A paper design: that outlines the theoretical planning for the project and inludes: a requirement analysis, subsystem design, acceptance test procedures and development timeline. 
- A first progress report: that outlines the simulated practical experimentation for the project and includes: a data analysis, experiment setup, results and acceptance test procedures. 
    - Data Analysis: jupyter notebook that plots the time and frequency domains and histograms of the provided sample 'Walking Around' data.
    - Code: includes the python scripts used in the simulated software implementation of the project.
- A second progress report: that outlines the practical experimentation for the project and includes: an IMU module, experiment setup, results and acceptance test procedures. 
    - Code: includes the C scripts used in the practical hardware implementation of the project.
    - Excel Speadsheets: inlcuding the results of the IMU validation tests and IMU comparison included in the IMU module.
- A final report: that contains the final handin for this course.
    -Code: includes the entire code base for the project to work in a "testing state". This testing state is what was used to generate the final results for the compression and encryption tests.

## Required Hardware
To get started working on this project, the following hardware is required:

| Hardware     | Quantity |
| :----------- | :-----------:|
| ICM-20649 Module | x 1|
| STM32f051 Discovery Board   | x 1|
| FTDI Adaptor   | x 1    |
| Micro-USB   | x 1 |
| Mini-USB   | x 1  |
| Male-to-Female Jumpers   | x 10  |
| Male-to-Male Jumpers   | x 10    |
| Computer to Code   | x 1    |

Note: The quantity of the jumpers stated is far beyond what is actually needed, however, jumpers are a really useful tool for debugging and so having many of them is highly recommended. 

## Required Software
As well as the above mentioned hardware, the following software/tools are needed:

| Hardware     | Quantity |
| :----------- | :-----------:|
| STM32 Cube IDE (Or equivalent such as VS Code) | x 1|
| Serial Port Monitor (Putty on Windows, or SerialTools on Mac) | x 1|

Note: The latest STM software needs to be loaded onto the STM32f051 for this project, this can be done with the STM32 Cube IDE software. 

## Connecting the Hardware
The pins on the WaveShare SenseHAT that need to be connected to the STM32f051 are the following:
| WaveShare HAT Pin     | STM32f051 Pin |
| :-----------: | :-----------:|
| GND | GND |
| 3.3V | 3.3V |
| SDA | PB7|
| SCL | PB6|

The pins on the FTDI adaptor that need to be connected to the STM32f051 are the following:
| FTDI Adaptor    | STM32f051 Pin |
| :-----------: | :-----------:|
| GND | GND |
| 5V | 5V |
| TX | PA10|
| RX | PA9|


## Run our Program
To run our program and test if all the connections are working properly, create a clone of the repository to your local machine, do this by running the following code:
```bash
cd storage_directory
```
```bash
git clone https://github.com/TashiSoldin/EEE3097S-Project.git
```
To get the latest version of the main branch, run:

```bash
git pull origin main
```
Open the STM32 Cube IDE or your preferred choice of development software and open the project file in the Final Report folder called "code". Build the code, and then upload it to your STM32f051 while it is plugged in to your computer.

The code should now be uploaded to the STM32f051. To moniter the ouput of the board connect the micro-usb from the HAT to your computer, a serial port monitor is needed. On a mac run the following command:
```bash
screen /dev/tty.usbserial-1420
```
This will open a serial monitor in the terminal which can be used to monitor the output of the HAT. Example output will look like the following:
```bash
00:25:49, 394, 20.9ºC, 53.8% RH 

Writing 0x14 to EEPROM address 0x189
Reading from EEPROM address 0x189
Received data: 20ºC
```
Alternativly, you can download the free serial software called "SerialTools" and use this to monitor your serial port of choice.

If Windows is being used, install the free software package called "Putty" to monitor the serial port. Instructions on how to setup Putty can be found on the following website: https://www.putty.org 


# General Git Commands

To create a clone of this repository, run the following commands:

```bash
cd storage_directory
```
```bash
git clone https://gitlab.com/g5332/eee3088F-HAT.git
```
To get the latest version of the main branch, run:

```bash
git pull origin main
```

To create a new branch, use the following bash command:

```bash
git checkout -b "newBranchName"
```
To merge branches, use the GitLab webpage.

Add all files to working tree:

```bash
git add .
```

Commit all files with a comment:

```bash
git commit -am "Message"
```
OR
```bash
git commit -a -m "Messaage"
```

To push to GitLab:

```bash
git push origin main
```
OR
```bash
git push
```
