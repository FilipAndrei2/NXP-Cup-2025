# NXP Cup 2025 – Autonomous Dual-Line Tracking Car

## Description

This repository contains the firmware developed by our team for the NXP Cup 2025 Netherlands European Finals.
The autonomous car navigates a dual-line track using real-time image processing with the Pixy 2 camera and PID-based control implemented in C/C++ on an NXP S32K microcontroller.

This project demonstrates advanced skills in embedded systems, computer vision, and control algorithms applied in a competitive robotics environment.

## Skills Acquired
- Embedded C programming
- Autonomous vehicle development
- Vector-based algorithms for trajectory and steering control
- Real-time image processing with Pixy 2
- Working with a track simulator written in Python for testing algorithms before implementing on our hardware
- First hands-on experience with computer vision in embedded systems

### Technologies

- **Hardware:** NXP S32K development board
- **Software:** C firmware using S32 Design Studio
- **Sensors:** Pixy 2 camera for track detection
- **Algorithms:** 
  - Steering is computed using a vector algebra algorithm: the normalized average between the vectors representing the track lines defines the desired trajectory. 
  - The steering angle is calculated as the angle between the car’s forward direction and the trajectory vector, then sent to the servo. 
  - A basic PID-based speed controller adjusts motor velocity based on the steering angle for stable navigation.


### Sensors: Pixy 2 camera for track detection

### Algorithms: 
Steering is computed using a vector algebra algorithm: the normalized average between the vectors representing the track lines defines the desired trajectory. The steering angle is calculated as the angle between the car’s forward direction and the trajectory vector, then sent to the servo. 
A basic speed controller adjusts motor velocity based on the steering angle for stable navigation.

