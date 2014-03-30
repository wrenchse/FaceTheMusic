//
//  analysis.h
//  FaceTheMusic
//
//  Created by Jonas Kjellberg on 3/26/14.
//
//

#ifndef __FaceTheMusic__analysis__
#define __FaceTheMusic__analysis__

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxFaceTrackerThreaded.h"

#include "ofxOsc.h"
#define HOST "localhost"
#define PORT 57110

using namespace ofxCv;
using namespace cv;


class analysis {
    
public: // place public functions or variables declarations here
    
    // methods, equivalent to specific functions of your class objects
    
    void update(ofImage fyce);
    void draw();
    void distancesRatio();
    void keyPressed(int key);

    ofxFaceTrackerThreaded tracker;
	ofVec2f position;
	float scale;
    
    int fejs;
    int vecpoint = 0;
    ofImage fejs1;
    ofImage fejs2;
    ofImage fejs3;
    ofImage fajs;
    ofImage fajscrop;
    
    vector<float> ratios;
	ofVec3f orientation;
	ofMatrix4x4 rotationMatrix;
	
	Mat translation, rotation;
	ofMatrix4x4 pose;
	
	ofEasyCam easyCam;
    
    bool thinking;
    bool restart = false;
    float startTime;
    
    ofxOscSender sender;
    ofxOscSender senderLang;
    
    analysis();  // constructor - used to initialize an object, if no properties are passed
    //               the program sets them to the default value
    
private: // place private functions or variables declarations here
    
};




#endif /* defined(__FaceTheMusic__analysis__) */
