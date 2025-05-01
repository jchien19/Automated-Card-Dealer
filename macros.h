#ifndef MACROS_H
#define MACROS_H

// define macros
#define MAXPLAYERS 6

#define DIV {60000, 10000, 10}

#define STEPPER_PIN_1 14 // To driver IN 1
#define STEPPER_PIN_2 12 // To driver IN 2
#define STEPPER_PIN_3 13 // To driver IN 3
#define STEPPER_PIN_4 15 // To driver in 4

// for wheel gear motor, temp value for now, need analog pin
#define MOTOR_PIN 32
// temporary value, need to calibrate (need to find value for ideal torque)
#define MOTOR_ANALOG_VALUE 50

// define buttons for game selection
#define BUTTON0 34 // B0 on board
#define BUTTON1 0 // B1 on board
#define BUTTON2 35 // B2 on board

#endif // MY_HEADER_H