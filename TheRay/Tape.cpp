//
//  Tape.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Tape.hpp"

int error = 0;
int lastError = 0;
int recentError = 0;

int kp = KP;
int kd = KD;

int q = 0;
int m = 0;

bool onLeft = false;
bool onMidLeft = false;
bool onMidRight = false;
bool onRight = false;


// Tape-following code, return error term to robot
int Tape::driveCorrection(bool defaultTurnRight) {
    
    bool left = onMidLeft;
    bool right = onMidRight;
    
    if (!left && !right) { // both off
        
        if (lastError > 0) error = 5;
        else if (lastError < 0) error = -5;
        
        else if (onLeft) error = -10;
        else if (onRight) error = 10;
        else error = 0;
    
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
    if (abs(error) < 10) return tapePresentSides();
    return false;
}

bool Tape::atIntersectionWithUpdate() {
    Tape::update();
    return atIntersection();
}

bool Tape::tapePresentCentre() {
    return onMidLeft || onMidRight;
}

bool Tape::tapePresentCentreWithUpdate() {
    onMidLeft = detectedTape(QRD_MIDLEFT);
    onMidRight = detectedTape(QRD_MIDRIGHT);
    return tapePresentCentre();
}


bool Tape::tapePresentSides() {
    return onLeft || onRight;
}

bool Tape::tapePresent() {
    return onMidLeft || onMidRight ||  onLeft || onRight;
}


bool Tape::tapePresentRight() {
    return onRight;
}

bool Tape::tapePresentLeft() {
    return onLeft;
}

Tape::IntersectionType Tape::tapePresentOnSide() {
    if (onRight) return Tape::Right;
    if (onLeft) return Tape::Left;
    return Tape::None;
}

bool Tape::detectedTape(int sensor) {
    return (analogRead(sensor) > THRESH_QRD);
}

void Tape::update(){
    onLeft = detectedTape(QRD_LEFT);
    onMidLeft = detectedTape(QRD_MIDLEFT);
    onMidRight = detectedTape(QRD_MIDRIGHT);
    onRight = detectedTape(QRD_RIGHT);
}


