//
//  Robot.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Robot.hpp"



Status Robot::cruise() {
    
    while (true) {
    switch (IR::check()) {
        case IR::None:
            //Serial.print("none");
            break;
        case IR::WeakLeft:
            //Serial.print("weak left");
            break;
        case IR::WeakRight:
            //Serial.print("weak right");
            break;
            
        case IR::StrongLeft:
            //Serial.print("strong left");

            return Status::IRLeft;
            break;
            
        case IR::StrongRight:
            //Serial.print("strong right");

            return Status::IRRight;
            break;
    }
    
    switch (Collision::check()) {
        case Collision::None:
            break;
        case Collision::Both:
            return Status::Collided;
            break;
        case Collision::Left:
            return Status::Collided;
            break;
        case Collision::Right:
            return Status::Collided;
            break;
        }
    
        if(atIntersection){
            return Status::Intersection;
        }
    
        Actuators::drive(Actuators::Normal, Tape::driveCorrection()); //TODO: change speed
        
    }
    
}

Status Robot::pickUpPassenger(bool rightSide) {
    
    int turnAngle = rightSide ? 90 : -90;
    Actuators::turnInPlace(turnAngle);
    
    Actuators::openClaw();
    Actuators::lowerArm();
    
    int approachStartTime = millis();
    Actuators::Velocity velocity = Actuators::Slow;
    
    Actuators::drive(velocity, Actuators::Straight);
    
    while (Collision::check() == Collision::None) {} // wait until both are tripped //TODO: change to allow for one tripping...
    
    int approachTime = millis() - approachStartTime;
   
    Actuators::stop();
    
    Actuators::closeClaw();
    
    delay(SERVO_OPERATION_TIME);
    
    Actuators::raiseArm();
    
    bool successful = !IR::frontDetected();
    
    Actuators::drive(velocity, Actuators::Straight, true);
    delay(approachTime);
    
    Actuators::stop();
    
    if(successful){
        return Status::PickupSuccessful;
    }
    return Status::PickupFailed;
}

Status Robot::dropOffPassenger(bool rightSide) {
    
    
}

void Robot::evade() {
    
    Actuators::drive(Actuators::Slow, Actuators::Straight, true);
    delay(500);
    Actuators::turnInPlace(400);
    cruise();
}
