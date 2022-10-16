# EEE3097S-Project

The following project design is for an ARM based digital IP using an STM32F051-microcontroller. This design aims to retrieve, compress and encrypt data from an Inertial Measurement Unit (IMU) sensor. This type of sensor includes an Accelerometer, a Gyroscope, a Magnetometer and a Barometer. This design will be implemented as a buoy installed on an ice 'pancake' in the Southern Ocean to collect data about the ice and wave dynamics. 

This data will then be transmitted using the Iridium communication network, which is a global satellite communications network. However, this is extremely costly and therefore the data would need to be compressed to reduce its size. The data is also encrypted for security purposes. 

This repository contains:
- A paper design: that outlines the theoretical planning for the project and inludes: a requirement analysis, subsystem design, acceptance test procedures and development timeline. 
- A first progress report: that outlines the simulated practical experimentation for the project and includes: a data analysis, experiment setup, results and acceptance test procedures. 
    - Data Analysis: jupyter notebook that plots the time and frequency domains and histograms of the provided sample 'Walking Around' data.
    - Code: includes the python scripts used in the simulated software implementation of the project.
- A second progress report: that outlines the practical experimentation for the project and includes: an IMU module, experiment setup, results and acceptance test procedures. 
    - Code: includes the C scripts used in the practical hardware implementation of the project.
    - Excel Speadsheets: inlcuding the results of the IMU validation tests and IMU comparison included in the IMU module.



