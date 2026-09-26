# Intelligent Ventilation System Using Arduino

## About the Project

The Intelligent Ventilation System is designed to automatically
control fan speed based on temperature and the number of people inside
the room.

## Components Used

- Arduino Uno
- DHT11 Temperature Sensors
- IR Sensors
- 16x2 I2C LCD
- L298N Motor Driver
- DC Fan

## Working

The DHT11 sensors measure the temperature and the IR sensors count
the number of people entering and leaving the room.

Based on the temperature and people count, the Arduino controls the
fan speed using PWM.

The LCD displays the temperature, people count and fan speed.

## Technologies

- Arduino
- Embedded C
- Sensors
- PWM
- IoT

## Future Scope

- Mobile monitoring
- Automatic window control
- Data logging
