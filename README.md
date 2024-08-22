Project Description:
This project involved developing a wireless environmental monitoring system using multiple sensors, with two slave devices and one master device. The system monitored environmental parameters such as temperature, humidity, gas concentration, wind speed, and wind direction. The collected data was transmitted wirelessly to the master device, which then processed and displayed the information.

Components Used:
Slave Device:

Arduino Uno
HC-06 Bluetooth module
DHT11 Temp/Humidity Sensor
MQ-135 Gas Sensor
Wind Vane Sensor
Solar Panel and Lithium Battery (for power)
Slave Devices:

Arduino Nano
HC-05 Bluetooth module
Infrared Flame Sensors
DHT11 Temp/Humidity Sensors
MQ-135 Gas Sensors
Communication Protocols Used:
UART (Universal Asynchronous Receiver-Transmitter):

How It’s Used:
UART was used for wireless communication between the master device and the slave devices via Bluetooth modules (HC-05/HC-06). The master and slave devices exchanged data using serial communication over Bluetooth.
The master device received sensor data from the slave devices through UART and processed it. This data was then sent to a connected computer or displayed on a serial monitor.
Purpose:
UART provided a simple and efficient way to establish wireless communication between multiple devices in the system, enabling real-time monitoring and control.
Analog Communication:

How It’s Used:
Analog communication was used for reading sensor values such as gas concentration from the MQ-135 sensor, wind direction from the wind vane, and analog values from the flame sensors. The Arduino's analogRead() function was employed to read these sensor values, which were then processed to determine environmental conditions.
Purpose:
Analog communication allowed the system to interpret varying sensor outputs (e.g., gas concentration levels, wind direction), which were crucial for monitoring the environment.
Simple Digital Communication:

How It’s Used:
Digital communication was utilized for simple binary sensors, such as detecting fire using the flame sensor (which outputs a digital HIGH or LOW depending on the presence of flame).
Digital pins on the Arduino were used to read the state of these sensors, providing straightforward true/false (1/0) data to the system.
