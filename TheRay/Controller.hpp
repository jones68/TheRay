//
//  Controller.hpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
//

#ifndef Controller_hpp
#define Controller_hpp

#include "Robot.hpp"
#include "Direction.hpp"
#include "Navigator.hpp"

class Controller {
    
    
    Direction turnDirection = StraightAhead;
    bool navigatorNotInitialized = true;
    
    
    void initializeNavigator();
    void initializePickup(bool rightSidePickup);
    void initializeDropoff();

public:
    
    Robot robot = Robot();
    Navigator navigator = Navigator();

    void execution();
};

#endif /* Controller_hpp */


