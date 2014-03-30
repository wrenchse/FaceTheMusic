//
//  gui.cpp
//  FaceTheMusic
//
//  Created by Jonas Kjellberg on 3/26/14.
//
//

#include "gui.h"


gui::gui(){
    
    kinect.setRegistration(true);
	kinect.init();
	kinect.open();		// opens first available kinect
	
    inpainter.setup(kinect.getWidth(), kinect.getHeight());
    inpainter.setInpaintingRadius(20);
	inpainter.setDownsampling(20);
    
	// print the intrinsic IR sensor values
	if(kinect.isConnected()) {
		ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
		ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
		ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
		ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
	}
    
	grayImage.allocate(kinect.width, kinect.height);
    inpaintImg.allocate(kinect.width, kinect.height);
    fajscrop.allocate(kinect.width, kinect.height,OF_IMAGE_COLOR);
	
	nearThreshold = 255;
	farThreshold = 240;
	
    numPixels = kinect.width * kinect.height;
	
	kinect.setCameraTiltAngle(angle);
	
	bDrawPointCloud = false;
    
    kinectprev.resize(640*480);
    kinectprevcolor.resize(640*480);
    kinectprevdis.resize(640*480);
    
    startTime = ofGetElapsedTimeMillis();
    eyeTime = PI/2;
    
    sender.setup(HOST, 57110);
    
    ofxOscMessage m;
    m.setAddress("/notify");
    m.addIntArg(1);
    sender.sendMessage(m);
    
    senderLang.setup(HOST, 57120);
    
    scaled = (ofGetHeight()/1080)*2;
    
}

//--------------------------------------------------------------
void gui::update(){
        
	kinect.update();
    
	if(kinect.isFrameNew()) {
        
        // CHECK FOR INTERACTION
        if (ofDist(pointX, pointY, kinect.width/2, kinect.height/2) < 50 && !takesnapshot) {
            if (touch == true) {
                startTime = ofGetElapsedTimeMillis();
                touch = false;
                
            } else if (ofGetElapsedTimeMillis()-startTime < 1000) {
                int colr = (ofGetElapsedTimeMillis()-startTime)/4;
                ofBackground(colr-55, colr, 0);
            } else {
                takesnapshot = true;
                ofxOscMessage v;
                v.setAddress("/gui");
                senderLang.sendMessage(v);
            }
        } else {
            ofBackground(200,50,100);
            touch = true;
            pointX = 0;
            pointY = 0;
        }        
		
        
        
        // UPDATE IMAGE
        inpaintImg.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
                
        // IF NOT SNAPSHOT ie UPDATE GUI WITH HANDTRACKING
        if (!takesnapshot){
            unsigned char * pix = inpaintImg.getPixels();

            for(int i = 0; i < numPixels; i++) {
                if(pix[i] < farThreshold) {
                    pix[i] = 0;
                }
            }
            
            
            // FIND BLOBS - ie HANDS
            contourFinder.findContours(inpaintImg, 10, (kinect.width/3*kinect.height/3), 1, false);

            if(contourFinder.nBlobs != 0) {
                pointX = contourFinder.blobs[0].boundingRect.getCenter().x;
                pointY = contourFinder.blobs[0].boundingRect.getCenter().y;
            }
                    
            
        } else {
            
            
            // IF SNAPSHOT IS ACTIVATED, DO FACE ANALYSIS
            inpainter.inpaint(inpaintImg);
            fajscrop.setFromPixels(kinect.getPixels(), 640, 480, OF_IMAGE_COLOR);
            
            unsigned char * pix = inpaintImg.getPixels();
            unsigned char * pix2 = fajscrop.getPixels();

            for(int i = 0; i < numPixels; i++) {
                if(pix[i] < farThreshold-50) {
                    pix2[i*3]   = 0;
                    pix2[i*3+1] = 0;
                    pix2[i*3+2] = 0;
                }
            }
            fajscrop.setFromPixels(pix2, 640, 480, OF_IMAGE_COLOR);
            

        }
    }
    
   
   
 
    
}

//--------------------------------------------------------------
void gui::draw(){
	
    if (!takesnapshot) {

            
            
            ofFill();
        
        if((ofGetElapsedTimeMillis()*1)%10000 > 9000 ) {
            eyeTime-= 0.02;
        } else {
            eyeTime = PI/2;
        }
        
            ofSetColor(255, 255, 255,20);
        ofEllipse(ofGetWidth()/4,ofGetHeight()/2, ofGetWidth()/2.5,
                  (ofGetHeight()/2.5 + ofGetHeight()/10*(sin(ofGetElapsedTimef()/5)))*sin(eyeTime));
        
        ofSetColor(0, 0, 0,10);
        ofEllipse(ofGetWidth()/4,ofGetHeight()/2, ofGetHeight()/2.6 + ofGetHeight()/10*(sin(ofGetElapsedTimef()/5)),
                  (ofGetHeight()/2.6 + ofGetHeight()/12*(sin(ofGetElapsedTimef()/5)))*sin(eyeTime));
        
        ofSetColor(255, 255, 255,20);
       // ofEllipse(ofGetWidth()/4,ofGetHeight()/2, ofGetHeight()/2.6 + ofGetHeight()/20*(sin(ofGetElapsedTimef())), (ofGetHeight()/2.6 + ofGetHeight()/12*(sin(ofGetElapsedTimef())))*sin(eyeTime));
        
            ofCircle(ofGetWidth()/4,ofGetHeight()/2, ((ofGetHeight()/10)+(ofGetHeight()/20)*abs(sin(ofGetElapsedTimef()))) *sin(eyeTime));
            ofSetColor(255, 255, 255);

        
        drawPointCloud();
    }
    
    

}


void gui::drawPointCloud() {
    
        int w = 640;
        int h = 480;
        ofMesh mesh;
        mesh.setMode(OF_PRIMITIVE_POINTS);
        int step = 5;
        
        for(int y = 0; y < h; y += step) {
            for(int x = 0; x < w; x += step) {
                int i = x+y*h;
                kinectprevdis[i] =  kinect.getDistanceAt(x, y); //0.4f * kinectprevdis[i] + 0.6f *
                
                if(kinectprevdis[i] > 500 && kinectprevdis[i] < 800.0) {
                    
                    kinectprev[i] = 0.8f * kinectprev[i] + 0.2f * kinect.getWorldCoordinateAt(x, y);
                    //ofColor color = (0);
                    mesh.addColor(0);
                    mesh.addVertex(kinectprev[i]);
                }
            }
        }
        
        glPointSize(4);
        ofPushMatrix();
    
    if (ofGetHeight() == 1080) {
        ofScale(2.25,2.25);
    }

        // the projected points are 'upside down' and 'backwards'
        ofScale(-1, 1, -1);
        ofScale(4,4);
        ofFill();
        mesh.drawVertices();
        ofPopMatrix();
    
}

//--------------------------------------------------------------
void gui::exit() {
	kinect.setCameraTiltAngle(0); // zero the tilt on exit
	kinect.close();
	
#ifdef USE_TWO_KINECTS
	kinect2.close();
#endif
}




