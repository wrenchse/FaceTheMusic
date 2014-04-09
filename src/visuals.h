//
//  visuals.h
//  FaceTheMusic
//
//  Created by Jonas Kjellberg on 3/26/14.
//
//

#ifndef __FaceTheMusic__visuals__
#define __FaceTheMusic__visuals__



#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxPostGlitch.h"
#include "faceVis.h"
//#include "faceVisKinect.h"
#include "wrBack.h"

#define HOST "localhost"
#define PORT 57110
#define NUM_MSG_STRINGS 20



class visuals {
    
public:
    
    void setup();
    void update(); 
    void draw(int offset);
    void keyPressed(int key);
    void keyReleased(int key);
    
    
    ofTrueTypeFont font;
    ofxOscSender sender;
    ofxOscReceiver receiver;
    
    
    string msg_string;
    string msg_strings;
    string mouseButtonState;
    
    
    float rms;
    float wave;
    float radius;    
    int h;
    int w;
    
    
    bool overlay = false;
    bool clearpicture = false;
    
    
    int picker = 0;
    int backpick = 0;
    int cellsize = 20;   // Dimensions of each cell in the grid
    int columns, rows;   // Number of columns and rows in our system
    int direction = 2;
    
    
    ofImage img;         // The source image
    ofImage sig;
    faceVis fejsy;
  //  faceVisKinect fejsK;
    wrBack backy;
    
    
    ofVec3f center;
    ofFbo			myFbo;
	ofxPostGlitch	myGlitch;
    
    
    visuals(); // constructor 
    
private: 
    
}; 

#endif