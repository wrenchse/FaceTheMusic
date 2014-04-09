//
//  wrBack.h
//  oscTester
//
//  Created by Jonas Kjellberg on 3/3/14.
//
//

#ifndef oscTester_wrBack_h
#define oscTester_wrBack_h

#include "ofMain.h"

class wrBack {
    
public: // place public functions or variables declarations here
    
    // methods, equivalent to specific functions of your class objects
    void update();  // update method, used to refresh your objects properties
    void draw(int pick);    // draw method, this where you'll do the object's drawing
    void setup();
    
    // variables
    float x;      // position
    float y;
    float speedY; // speed and direction
    float speedX;
    float size;
    
    int w = ofGetWidth()/2;
    int h = ofGetHeight();
    
    
    wrBack(); // constructor - used to initialize an object, if no properties are passed
    //               the program sets them to the default value
    
private: // place private functions or variables declarations here
    
}; // dont't forget the semicolon!!





#endif
