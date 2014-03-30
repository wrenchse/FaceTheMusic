//
//  gui.h
//  FaceTheMusic
//
//  Created by Jonas Kjellberg on 3/26/14.
//
//

#ifndef FaceTheMusic_gui_h
#define FaceTheMusic_gui_h

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxKinectInpainter.h"
#include "ofxOpenCv.h"

#include "ofxOsc.h"
#define HOST "localhost"
#define PORT 57110



class gui {
    
public: // place public functions or variables declarations here
    
    // methods, equivalent to specific functions of your class objects
    
    void update();
    void draw();
    void drawPointCloud();
    void exit();
    
    ofxKinect kinect;
    ofxKinectInpainter inpainter;
    ofxOscSender sender;
    ofxOscSender senderLang;
    
	ofxCvGrayscaleImage grayImage; // grayscale depth image
    ofxCvGrayscaleImage inpaintImg; // grayscale depth image
    ofxCvContourFinder contourFinder;
    
    ofImage fajscrop;
   	ofEasyCam easyCam;

    vector<ofVec3f> kinectprev;
    vector<ofColor> kinectprevcolor;
    vector<float>   kinectprevdis;
    
	bool bDrawPointCloud;
    bool touch = false;
    bool takesnapshot;
	
	int nearThreshold;
	int farThreshold;
    int numPixels;
	int angle;
    int pointX,pointY;
    
    float startTime;
    float eyeTime;
    
    double scaled;
    
    gui();  // constructor - used to initialize an object, if no properties are passed
            //               the program sets them to the default value
    
private: // place private functions or variables declarations here
    
};


#endif
