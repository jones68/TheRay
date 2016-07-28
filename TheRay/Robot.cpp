//
//  Robot.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Robot.hpp"

unsigned long lastIntersectionTime = millis();

void Robot::turnAtIntersection(Direction direction){
    
    unsigned long time = millis();
    
    //Serial.print(direction);
    
    switch (direction) {
        case StraightAhead:
            break;
        case Left:
            Serial.println("WE MADE THE LEFT");
            Tape::update();
            while (!Tape::tapePresentLeft() && (millis() - time) < TIME_IN_INTERSECTION) {
                Tape::update();
                Actuators::drive(Actuators::Fast, Tape::driveCorrection());
            }
            Actuators::turnIntersection(false);
            while (!Tape::tapePresentCentreWithUpdate()) {}
            break;
        case Right:
            Tape::update();
            while (!Tape::tapePresentRight() && (millis() - time) < TIME_IN_INTERSECTION) {
                Tape::update();
                Actuators::drive(Actuators::Fast, Tape::driveCorrection());
            }
            Actuators::turnIntersection(true);
            while (!Tape::tapePresentCentreWithUpdate()) {}
            break;
        case TurnAround:
            turnOntoTape(direction);
            break;
    }

}

Status Robot::cruise(Direction direction) {
    
    turnAtIntersection(direction);
    
    while (true) {
        
        Collision::update();
        Tape::update();
        IR::update();
        
//        switch (IR::check()) { //IR Check
//                
//            case IR::None:
//                driveVelocity = Actuators::Normal;
//                break;
//                
//            case IR::WeakLeft:
//                driveVelocity = Actuators::Slow;
//                break;
//                
//            case IR::WeakRight:
//                driveVelocity = Actuators::Slow;
//                break;
//                
//            case IR::StrongLeft:
//                Actuators::stop();
//                return IRLeft;
//                break;
//                
//            case IR::StrongRight:
//                Actuators::stop();
//                return IRRight;
//                break;
//        }
        
        if (Collision::occured()) return Collided;
        
        if (Tape::atIntersection() && (millis() - lastIntersectionTime) > TIME_FREE_OF_INTERSECTION) {
            lastIntersectionTime = millis();
            return Intersection;
        }

        Actuators::drive(driveVelocity, Tape::driveCorrection());
    }
}


void Robot::turnOntoTape(Direction direction) {
    
    switch (direction) {
            
        case StraightAhead:
            break;
            
        case Left:
            Actuators::turnInPlace(TURN_OFF_TAPE_DURATION, false);
            while (!Tape::tapePresentCentreWithUpdate()) {}
            break;
            
        case Right:
            Actuators::turnInPlace(TURN_OFF_TAPE_DURATION, true);
            while (!Tape::tapePresentCentreWithUpdate()) {}
            break;
            
        case TurnAround:
            Actuators::turnInPlace(TURN_180, true);
            while (!Tape::tapePresentCentreWithUpdate()) {}
            break;
    }
}

void Robot::pickUpPassenger(bool turnRightBefore, bool turnRightAfter) {
    
    Actuators::drive(Actuators::Slow, Actuators::Straight);
    delay(DRIVE_FORWARD_BEFORE_TURNING_WHEN_DETECTED_IR);

    int duration = TURN_FOR_PASSENGER_PICKUP_DURATION;
    
    Actuators::turnInPlace(duration, turnRightBefore);
    Actuators::stop();
    
    Actuators::openClaw();
    Actuators::lowerArm();
    
    unsigned long approachStartTime = millis();
    Actuators::Velocity velocity = Actuators::Slow;
    
    Actuators::drive(velocity, Actuators::Straight);
    
    while (!Collision::occuredWithUpdate()) {} // wait until both are tripped
    
    unsigned long approachTime = millis() - approachStartTime;
   
    Actuators::stop();
    
    Actuators::closeClaw();
    
    delay(SERVO_OPERATION_TIME);
    
    Actuators::raiseArm();
    
    bool successful = true; //!IR::frontDetected();
    
    Actuators::drive(velocity, Actuators::Straight, true);
    
    unsigned long backupStartTime = millis();
    
    while(millis() - backupStartTime < (approachTime)){
        Tape::update();
        
        if (Tape::tapePresent()){
            break;
        }
    }
    
    Actuators::turnInPlace(turnRightAfter, true);
    while(!Tape::tapePresentCentreWithUpdate()) {}

    Actuators::stop();
}

void Robot::dropOffPassenger(Direction direction, bool rightSideDropOff) {
    
    turnAtIntersection(direction);

    
    unsigned long time = millis();
    
    while( (millis() - time) < DROP_OFF_APPROACH_TIME ){
        Tape::update();
        Actuators::drive(Actuators::Fast, Tape::driveCorrection());
    }
    
    Actuators::turnInPlace(TURN_FOR_PASSENGER_DROPOFF_DURATION, rightSideDropOff);
    
    Actuators::drive(Actuators::Slow, Actuators::Straight); //drive up to drop off platform
    delay(DROP_OFF_PASSENGER_DRIVE_OFF_TRACK_DELAY);
    
    Actuators::stop();
    
    Actuators::lowerArm();
    Actuators::openClaw();
    
    delay(OPEN_FINGERS_FOR_PASSENGER_DROP_OFF_DURATION);
    
    Actuators::drive(Actuators::Slow, Actuators::Straight, true); //get back onto track
    
    delay(DROP_OFF_PASSENGER_DRIVE_OFF_TRACK_DELAY);
    
    Actuators::stop();
    
    Actuators::closeClaw();
    Actuators::raiseArm();
    
    Actuators::turnInPlace(!rightSideDropOff, true);
    while(!Tape::tapePresentCentreWithUpdate()){}
}

void Robot::evade() {
    
    Actuators::drive(Actuators::Slow, Actuators::Straight, true);
    delay(REVERSE_TIME_EVADE);
    
    Actuators::turnInPlace(TURN_180, false);
    while (!Tape::tapePresentCentreWithUpdate()) {}
}

bool Robot::turnAndScan(){
    unsigned long time = millis();
    Actuators::turnInPlace(true, false);
    bool irDetected = false;
    while(millis() - time < TURN_180 && !Tape::tapePresentCentreWithUpdate()){
        if (!irDetected && IR::checkLeftWithUpdate()){
            irDetected = true;
        }
    }
    return irDetected;
}