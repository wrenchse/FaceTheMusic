//
//  faceVisKinect.h
//  FaceTheMusic
//
//  Created by Jonas Kjellberg on 4/9/14.
//
//

#ifndef __FaceTheMusic__faceVisKinect__
#define __FaceTheMusic__faceVisKinect__

#include "ofMain.h"
#include "ofxDelaunay.h"

class faceVisKinect {
    
public: // place public functions or variables declarations here
    
    // methods, equivalent to specific functions of your class objects
    void update(float rms);  // update method, used to refresh your objects properties
    void draw();    // draw method, this where you'll do the object's drawing
    void setup();
    
    
    float rms;
    int w;
    int h;
    float offset;
    int cellsize;
    
    ofImage texImage;
    
    vector<float> xx;
    vector<float> size;
    
    vector<ofVec3f> depth;
    
    ofxDelaunay triangulation;
    
    faceVisKinect(); // constructor - used to initialize an object, if no properties are passed
    //               the program sets them to the default value
    
private: // place private functions or variables declarations here
    
}; // dont't forget the semicolon!!


#endif /* defined(__FaceTheMusic__faceVisKinect__) */
