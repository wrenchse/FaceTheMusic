#ifndef _FACE_VIS    // if this class hasn't been defined, the program can define it
#define _FACE_VIS    // by using this if statement you prevent the class to be called more
                    // than once which would confuse the compiler

#include "ofMain.h"
#include "ofxDelaunay.h"

class faceVis {
    
public: // place public functions or variables declarations here
    
    // methods, equivalent to specific functions of your class objects
    void update(float rms);  // update method, used to refresh your objects properties
    void draw(int picky, int wave);    // draw method, this where you'll do the object's drawing
    void setup(ofImage img);
    

    float rms;
    int w;
    int h;
    float offset;
    int cellsize;
    
    ofImage texImage;
    
    vector<float> xx;
    vector<float> size;
    
    ofxDelaunay triangulation;
    
    faceVis(); // constructor - used to initialize an object, if no properties are passed
    //               the program sets them to the default value
    
private: // place private functions or variables declarations here
    
}; // dont't forget the semicolon!!

#endif