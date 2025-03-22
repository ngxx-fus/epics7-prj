# EPICS

  EPICS is an acronym for Engineering Projects in Community Service.

## About the reposistory

  This reposistory contains a part of the project of my team. Writing in C++ using FreeRTOS and Arduino framework.

## About the module

  This module will use 05 ultrasonic sensors to measure distances, thereby detecting obstacles in front of the wearer. Each ultrasonic sensor has a maximum range of 6 meters and a detection angle of up to 75 degrees. After collecting distance information, the secondary processor (using the ESP-WROOM32 development kit) will compare the data with preset conditions and issue warnings through two pulse buzzers on either side. Additionally, the secondary processor will send a copy of the information received from the sensors to the main processor.

