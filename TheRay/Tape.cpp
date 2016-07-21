//
//  Tape.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Tape.hpp"

Tape::IntersectionType firstIntersectionDirection = Tape::None;


int error = 0;
int lastError = 0;
int recentError = 0;

int kp = KP;
int kd = KD;

int q = 0;
int m = 0;


bool Tape::detectedTape(int sensor) {
    return (analogRead(sensor) > THRESH_QRD);
}

// Tape-following code, return error term to robot

int Tape::driveCorrection() {
    return driveCorrection(true);
}

int Tape::driveCorrection(bool defaultTurnRight) {
    
    bool left = detectedTape(QRD_MIDLEFT);
    bool right = detectedTape(QRD_MIDRIGHT);
    
    if (!left && !right) { // both off
        
        if (lastError > 0) error = 5;
        else if (lastError < 0) error = -5;
        
        else if (defaultTurnRight) error = 5; //turn in preffered direction if both off and no last error-term
        else error = -5;
        
    } else { // tape found
        if (left && right) error = 0;
        else if (left && !right) error = -1; // turn left
        else if (!left && right) error = +1; // turn right
    }
    
    if (error != lastError) {
        recentError = lastError;
        q = m;
        m = 1;
    }
    
    int p = kp * error;
    int d = (int)((float)kd * (float)(error - recentError) / (float)(q + m));
    int con = p + d;
    
    m++;
    lastError = error;
    
    return con;
}


// Intersection detection
bool Tape::atIntersection() {
    
    if (firstIntersectionDirection == Tape::None) {
        
        if (detectedTape(QRD_LEFT)) {
            firstIntersectionDirection = Tape::Left;
            return true;
        } else if (detectedTape(QRD_RIGHT)) {
            firstIntersectionDirection = Tape::Right;
            return true;
        } else {
            return false;
        }
    }
    
    return detectedTape(QRD_RIGHT) || detectedTape(QRD_RIGHT);
}

Tape::IntersectionType Tape::tapePresentSide() {
    if (detectedTape(QRD_RIGHT)) return Tape::Right;
    if (detectedTape(QRD_LEFT)) return Tape::Left;
    return Tape::None;
}

bool Tape::tapePresentCentre() {
    return detectedTape(QRD_MIDLEFT) || detectedTape(QRD_MIDRIGHT);
}

bool Tape::tapePresent() {
    return detectedTape(QRD_MIDLEFT) || detectedTape(QRD_MIDRIGHT) ||  detectedTape(QRD_LEFT) || detectedTape(QRD_RIGHT);
}

Tape::IntersectionType Tape::firstIntersectionDirectionStored() {
    return firstIntersectionDirection;
}


