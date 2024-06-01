# Component List and Pin Configuration

This document provides a list of components used in the project along with their descriptions, pin configurations, manufacturer information, quantities, and images.

## Components

| Component          | Description                    | Pin Configuration                                                                                     | Manufacturer                     | Qty | Images  |
|--------------------|--------------------------------|-------------------------------------------------------------------------------------------------------|----------------------------------|-----|---------|
| DHT11 Sensor       | Indoor Temperature Sensor      | G: A pin that connects to ground<br>V: A pin that connects to a +5V power supply<br>S: A pin that connects to digital port. In our case, our digital pin is 13 |                                  | 1   | ![DHT11 Sensor](../doc/images/COMPONENTS_DHT11.png) |
| 47KResistor        | LM35                           | LM35                                                                                                  |                                  |     |         |
| 10KResistor        | Resistance Photo resistor      |                                                                                                       | KS0505 (STEM Starter Kit for Arduino) | 2   | ![10KResistor](image_path) |
| 220Resistor        | Resistance LED                 | LED                                                                                                   | KS0505 (STEM Starter Kit for Arduino) | 1   | ![220Resistor](image_path) |
| 3,3KResistor       | Resistance Motor DC/TIP122     | TIP122                                                                                                | KS0505 (STEM Starter Kit for Arduino) | 1   |         |
| 4,7KResistor       | Resistance DHT11               | DHT11                                                                                                 | KS0505 (STEM Starter Kit for Arduino) | 1   |         |
| 1602 I2C LCD       | LCD information screen         | GND: A pin that connects to ground<br>VCC: A pin that connects to a +5V power supply<br>SDA: A pin that connects to analog port A4 for IIC communication<br>SCL: A pin that connects to analog port A5 for IIC communication | KS0505 (STEM Starter Kit for Arduino) | 1   | ![1602 I2C LCD](image_path) |
| 130 Motor Propeller| Fan                            | 130 Dc Motor                                                                                          | KS0505 (STEM Starter Kit for Arduino) | 1   | ![130 Motor Propeller](image_path) |
| 130 Dc Motor       | DC motor for fan               | Pin 3                                                                                                 | KS0505 (STEM Starter Kit for Arduino) | 1   | ![130 Dc Motor](image_path) |
| Stepper Motor      | Motor for opening and closing shutters | Pin 8, 9, 10, 11                                                                                        | KS0505 (STEM Starter Kit for Arduino) | 1   | ![Stepper Motor](image_path) |
| PIR motion Sensor  | Motion Sensor                  | G: A pin that connects to ground<br>V: A pin that connects to a +5V power supply<br>S: A pin that connects to digital port. In our case, our digital pin is 2  | KS0505 (STEM Starter Kit for Arduino) | 1   | ![PIR motion Sensor](image_path) |
| Servo Motor        | Opening and closing of window  | Black line is for GND<br>Red one for power 5V<br>Yellow one for signal terminal (PWM signal). In our case, our digital pin is 7 | KS0505 (STEM Starter Kit for Arduino) | 1   | ![Servo Motor](image_path) |
| Photoresistor      | Illumination Sensor            | Pin A2, A1                                                                                             | KS0505 (STEM Starter Kit for Arduino) | 2   | ![Photoresistor](image_path) |
| LED-Red            | Indoor light bulb home         | Digital Pin 6                                                                                          | KS0505 (STEM Starter Kit for Arduino) | 4   | ![LED-Red](image_path) |
| TIP122 Transistor  | Auxiliary DC motor             | Pin ground<br>Pin 130 Dc Motor<br>Pin 5V                                                               | KS0505 (STEM Starter Kit for Arduino) | 1   | ![TIP122 Transistor](image_path) |
| LM35 Temp Sensor   | Analog temperature sensor      | Pin A0                                                                                                 | KS0505 (STEM Starter Kit for Arduino) | 1   | ![LM35 Temp Sensor](image_path) |
| Breadboard         | Connection board               |                                                                                                       |                                  | 2   | ![Breadboard](image_path) |

## Notes
- All components are from the KS0505 STEM Starter Kit unless otherwise specified.
- Ensure to connect each component to the correct pins as described to avoid any malfunction.