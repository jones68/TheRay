//
//  Config.hpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
//

#ifndef Config_hpp
#define Config_hpp

// Tape
#define THRESH_QRD 120

#define KP 22
#define KD 25
#define KI 0
#define K 100

#define CLOCK_FREQUENCY 1200
#define TAPE_LOST_ERROR 1000
#define INTIAL_FIND_TAPE_DURATION 100

#define LOST_COUNT_LIMIT_FOR_INTERSECTION_DETECTION 200
#define LOST_COUNT_LIMIT_FOR_SEARCH 300 // larger than limit for intersection detection

#define SLIGHT_RIGHT_AT_SPECIAL_INTERSECTION_TURN 30
#define SLIGHT_RIGHT_AT_SPECIAL_INTERSECTION_DURATION 120


// IR
#define THRESH_LOW_IR 13
#define THRESH_HIGH_IR 27
#define THRESH_CAP_IR 30

#define THRESH_FRONT_IR 65

#define IR_AVERAGING_SAMPLE_SIZE 3


// Robot operations

// Collision
#define REVERSE_TIME_EVADE 200
#define NUMBER_OF_SWITCH_CHECKS 2


// Intersection
#define TIME_MIN_BETWEEN_INTERSECTIONS 500
#define TIME_FREE_OF_INTERSECTION 1000
#define TIME_IN_INTERSECTION 200

// Turns
#define TURN_IN_PLACE_VELOCITY 100
#define TURN_OFF_TAPE_DURATION 100
#define TURN_180_DURATOIN 900

#define INTERSECTION_TURN_VELOCITY 150
#define INTERSECTION_TURN_DELAY 250

#define TURN_SLIGHT 5
#define TURN_HARD 15


#define GETTING_UNSTUCK_STARTING_TIME 1200
#define GETTING_UNSTUCK_DELAY 100


// Pickup
#define TURN_FOR_PASSENGER_PICKUP_DURATION 550
#define DRIVE_FORWARD_BEFORE_TURNING_WHEN_DETECTED_IR 150
#define APPROACH_MAX_TIME 450

 // ** Special pickup delays

#define TIME_19_TO_16_MAX_TIME 1666
#define TIME_16_TO_19_MIN_TIME 1000

#define TIME_1_TO_6_MAX_TIME_LEFT 1666
#define TIME_1_TO_6_MAX_TIME_RIGHT 1800
#define TIME_6_TO_1_MIN_TIME 1000



#define TIME_17_TO_16_MAX_TIME 1000
#define TIME_16_TO_17_MIN_TIME 400

#define TIME_7_TO_6_MAX_TIME 1000
#define TIME_6_TO_7_MIN_TIME 400



#define TIME_12_TO_8_MAX_TIME 2600
#define TIME_12_TO_8_MIN_TIME 500


#define TIME_16_TO_14_MIN_TIME 400

#define TIME_8_TO_10_MAX_TIME 1700
#define TIME_12_TO_10_MAX_TIME 2000



// Dropoff
#define DROP_OFF_APPROACH_TIME 900
#define TURN_FOR_PASSENGER_DROPOFF_DURATION 410
#define DROP_OFF_PASSENGER_DRIVE_OFF_TRACK_DELAY 300
#define OPEN_FINGERS_FOR_PASSENGER_DROP_OFF_DURATION 400


// Velocities
#define VELOCITY_SLOW 110
#define VELOCITY_NORMAL 150
//#define VELOCITY_FAST 220
//#define VELOCITY_NITROUS 255

#define VELOCITY_PICKUP 130

#define ACCELERATION_FACTOR .3
#define START_VELOCITY 70

#define KICKBACK 35

#define VELOCITY_ARM 100


// Pin connectors

// SERVO ANGLES

#define SERVO_OPEN 15
#define SERVO_CLOSED 90
#define SERVO_OPERATION_TIME 500 //millis

// QRD (ANALOG)

#define QRD_RIGHT 7
#define QRD_LEFT 4
#define QRD_MIDRIGHT 6
#define QRD_MIDLEFT 5

// IR (ANALOG)

#define IR_RIGHT 0
#define IR_MIDRIGHT 1
#define IR_MIDLEFT 2
#define IR_LEFT 3

// ULTRASONIC (DIGITAL)

#define ULTRASONIC_TRIG 1
#define ULTRASONIC_ECHO 2

// TOUCH SWITCHES (DIGITAL)

#define TOUCH_SWITCH_RIGHT 0
#define TOUCH_SWITCH_LEFT 1
#define TOUCH_SWITCH_ARM_UP 4 //lower switch
#define TOUCH_SWITCH_ARM_DOWN 5 //upper switch

// MOTORS

#define MOTOR_SERVO 0
#define MOTOR_RIGHT 2
#define MOTOR_LEFT 1
#define MOTOR_ARM 0

// Positive for right is forward, negative for left is forward
#define MOTOR_ARM_SIGN_UP 1
#define MOTOR_LEFT_SIGN_UP 1
#define MOTOR_RIGHT_SIGN_UP 1


#endif

   

