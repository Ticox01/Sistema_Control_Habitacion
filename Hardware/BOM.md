# Component List and Pin Configuration

This document provides a list of components used in the project along with their descriptions, pin configurations, manufacturer information, quantities, and images.

## Components

| Component          | Description                    | Pin Configuration                                                                                     | Manufacturer                     | Qty | Images  |
|--------------------|--------------------------------|-------------------------------------------------------------------------------------------------------|----------------------------------|-----|---------|
| DHT11 Sensor       | Indoor Temperature Sensor      | G: A pin that connects to ground<br>V: A pin that connects to a +5V power supply<br>S: A pin that connects to digital port. In our case, our digital pin is 13 |                                  | 1   | ![DHT11 Sensor](../doc/images/COMPONENTS_DHT11.png) |
| 47K Resistor        | LM35                           | LM35                                                                                                  |                                  |     |  ![4,7kResistor](../doc/images/COMPONENTS_47K.PNG)       |
| 10K Resistor        | Resistance Photo resistor      |                                                                                                       | KS0505 (STEM Starter Kit for Arduino) | 2   | ![10kResistor](../doc/images/COMPONENTS_10K.PNG) |
| 220 Resistor        | Resistance LED                 | LED                                                                                                   | KS0505 (STEM Starter Kit for Arduino) | 1   | ![220Resistor](../doc/images/COMPONENTS_220.PNG) |
| 3,3K Resistor       | Resistance Motor DC/TIP122     | TIP122                                                                                                | KS0505 (STEM Starter Kit for Arduino) | 1   | ![3,3k_Resistor](../doc/images/COMPONENTS_33K.PNG)        |
| 4,7K Resistor       | Resistance DHT11               | DHT11                                                                                                 | KS0505 (STEM Starter Kit for Arduino) | 1   | ![4,7k_Resistor](../doc/images/COMPONENTS_47K.PNG)      |
| 1602 I2C LCD       | LCD information screen         | GND: A pin that connects to ground<br>VCC: A pin that connects to a +5V power supply<br>SDA: A pin that connects to analog port A4 for IIC communication<br>SCL: A pin that connects to analog port A5 for IIC communication | KS0505 (STEM Starter Kit for Arduino) | 1   | ![1602 I2C LCD](../doc/images/COMPONENTS_LCDI2C.png) |
| 130 Motor Propeller| Fan                            | 130 Dc Motor                                                                                          | KS0505 (STEM Starter Kit for Arduino) | 1   | ![130 Motor Propeller](../doc/images/COMPONENTS_FAN.png) |
| 130 Dc Motor       | DC motor for fan               | Pin 3                                                                                                 | KS0505 (STEM Starter Kit for Arduino) | 1   | ![130 Dc Motor](../doc/images/COMPONENTS_DCMOTOR.png) |
| Stepper Motor      | Motor for opening and closing shutters | Pin 8, 9, 10, 11                                                                                        | KS0505 (STEM Starter Kit for Arduino) | 1   | ![Stepper Motor](../doc/images/COMPONENTS_STEPPER.png) |
| PIR motion Sensor  | Motion Sensor                  | G: A pin that connects to ground<br>V: A pin that connects to a +5V power supply<br>S: A pin that connects to digital port. In our case, our digital pin is 2  | KS0505 (STEM Starter Kit for Arduino) | 1   | ![PIR motion Sensor](../doc/images/COMPONENTS_PIR.png) |
| Servo Motor        | Opening and closing of window  | Black line is for GND<br>Red one for power 5V<br>Yellow one for signal terminal (PWM signal). In our case, our digital pin is 7 | KS0505 (STEM Starter Kit for Arduino) | 1   | ![Servo Motor](../doc/images/COMPONENTS_SERVO.png) |
| Photoresistor      | Illumination Sensor            | Pin A2, A1                                                                                             | KS0505 (STEM Starter Kit for Arduino) | 2   | ![Photoresistor](../doc/images/COMPONENTS_LDR.png) |
| LED-Red            | Indoor light bulb home         | Digital Pin 6                                                                                          | KS0505 (STEM Starter Kit for Arduino) | 4   | ![LED-Red](../doc/images/COMPONENTS_LED.png) |
| TIP122 Transistor  | Auxiliary DC motor             | Pin ground<br>Pin 130 Dc Motor<br>Pin 5V                                                               | KS0505 (STEM Starter Kit for Arduino) | 1   | ![TIP122 Transistor](../doc/images/COMPONENTS_TIP122.png) |
| LM35 Temp Sensor   | Analog temperature sensor      | Pin A0                                                                                                 | KS0505 (STEM Starter Kit for Arduino) | 1   | ![LM35 Temp Sensor](../doc/images/COMPONENTS_LM35.png) |
| Breadboard         | Connection board               |                                                                                                       |                                  | 2   | |
| KEYESTUDIO Plus Development Board         | Arduino board               |                                                                                                       | KS0505 (STEM Starter Kit for Arduino) | 1   | ![Arduino Board](../doc/images/Arduino_board.PNG) |

## Notes
- All components are from the KS0505 STEM Starter Kit unless otherwise specified.
- Ensure to connect each component to the correct pins as described to avoid any malfunction.
