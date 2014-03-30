#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    
    ofSetFrameRate(600);
    ofSetVerticalSync(false);

    fonten.loadFont("Letter Gothic Std", height/6);
}

//--------------------------------------------------------------
void testApp::update(){
    
    
    gui.update();
   
    
    if(gui.kinect.isFrameNew() && gui.takesnapshot){
        ofBackground(50, 250, 50);
        if(ofGetElapsedTimeMillis()-timer > 2000) {
        analysis.update(gui.fajscrop);
        } 
       
        
    } else if (!gui.takesnapshot){
        timer = ofGetElapsedTimeMillis();
    }
    
     visuals.update();
}

//--------------------------------------------------------------
void testApp::draw(){

  
    gui.draw();
   
    if(gui.takesnapshot && analysis.thinking) {
        
       
        ofSetColor(150, 250, 100);
        ofRect(0, height/3, ofMap(analysis.startTime, 0, 200, 0, width), height/3);
        
        ofPushMatrix();
        ofTranslate(width/4, height/2);
        ofRotateY(ofGetElapsedTimef()*200);
        
        ofScale(height/(height/10),height/(height/12),2);
        
        analysis.draw();
        ofPopMatrix();
        
        ofDrawBitmapString("SCANNING", 10, 20);
        if(analysis.restart) {
            gui.takesnapshot = false;
            analysis.thinking = false;
        }
        
    } else if (gui.takesnapshot) {
        
        ofSetColor(0,50);
        ofLine(0, (height/2)+(sin(ofGetElapsedTimef())*(height/2)), width,
               (height/2)+(sin(ofGetElapsedTimef())*(height/2)) );
        ofLine(0, (height/2)+(sin(ofGetElapsedTimef()*1.43)*(height/2)), width,
               (height/2)+(sin(ofGetElapsedTimef()*1.43)*(height/2)) );
        ofLine(0, (height/2)+(sin(ofGetElapsedTimef()*1.77)*(height/2)), width,
               (height/2)+(sin(ofGetElapsedTimef()*1.77)*(height/2)) );
        
        if(ofGetFrameNum()%9 < 5)
        fonten.drawString("SEARCHING", 0, height/2.25);
        
        
        ofSetColor(255);
        stringstream reportStream;
        reportStream << 11*ofGetFrameNum()%10000 << ofGetFrameRate() << endl
        << ofGetFrameRate() << ofGetFrameNum()%10000 << endl;
        ofDrawBitmapString(reportStream.str(), 20, ofGetHeight()-50);
    }
    
    
    visuals.draw(width/2);
    
    
}


void testApp::exit() {
    
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    visuals.keyPressed(key);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    visuals.keyReleased(key);
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
