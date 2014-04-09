#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxPostGlitch.h"
#include "updateThread.h"

// Klasser
#include "gui.h"
#include "analysis.h"
#include "visuals.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void exit();
    
    int width = ofGetWidth();
    int height = ofGetHeight();
    int timer;
    
    gui gui;
    analysis analysis;
    visuals visuals;
    
    vector <ofVec3f> depth;
   
    
    ofTrueTypeFont fonten;
 		
};
