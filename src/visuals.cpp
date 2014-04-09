//
//  visuals.cpp
//  FaceTheMusic
//
//  Created by Jonas Kjellberg on 3/26/14.
//
//

#include "visuals.h"

//--------------------------------------------------------------
visuals::visuals() {
    
    img.loadImage("face.jpg");  // Load the image
    fejsy.setup(img);
    
	// open an outgoing connection to HOST:PORT
	sender.setup(HOST, 57110);
    
	receiver.setup(9000);
    
    ofxOscMessage m;
    m.setAddress("/notify");
    m.addIntArg(1);
    sender.sendMessage(m);
    sender.sendMessage(m);
    
    myFbo.allocate(ofGetWidth(), ofGetHeight());
	myGlitch.setup(&myFbo);    
}


//--------------------------------------------------------------
void visuals::update(){
    
	while(receiver.hasWaitingMessages()){

		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
        if(m.getAddress() == "/rms")  rms = m.getArgAsFloat(0)*2;
        
        string msg_string;
        
		msg_string += ofToString(m.getArgAsFloat(0));
		msg_strings = msg_string;
	}
    
    
    myFbo.begin();
    if (!clearpicture)
        ofClear(0, 0, 0,255);
    fejsy.update(rms);
    backy.draw(backpick);
    fejsy.draw(picker,wave);
    myFbo.end();    
}


//--------------------------------------------------------------
void visuals::draw(int offset){

    wave = sin(ofGetElapsedTimef()/10)-1;

    myGlitch.generateFx();
    myFbo.draw(offset,0);
    
    if (overlay){
        ofPushMatrix();
        ofTranslate(offset,0);
        fejsy.draw(picker,wave);
        ofPopMatrix();
    }
    
    //fejsK.draw();

}

//--------------------------------------------------------------
void visuals::keyPressed(int key){
	

    if (key == 'a') picker = 0;
    if (key == 's') picker = 1;
    if (key == 'd') picker = 2;
    if (key == 'f') picker = 3;
    if (key == 'g') picker = 4;
    if (key == 'h') picker = 5;
    if (key == 'j') picker = 6;
    
    if (key == 'z') backpick = 0;
    if (key == 'x') backpick = 1;
    if (key == 'c') backpick = 2;
    if (key == 'v') backpick = 3;
    if (key == 'b') backpick = 4;
    if (key == 'n') backpick = 5;
    if (key == 'm') backpick = 6;
    
    if (key == ' ') overlay = !overlay;
    if (key == 'l') clearpicture = !clearpicture;
    
    //Glitch-switch
    {
        if (key == '1') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, true);
        if (key == '2') myGlitch.setFx(OFXPOSTGLITCH_GLOW			, true);
        if (key == '3') myGlitch.setFx(OFXPOSTGLITCH_SHAKER			, true);
        if (key == '4') myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, true);
        if (key == '5') myGlitch.setFx(OFXPOSTGLITCH_TWIST			, true);
        if (key == '6') myGlitch.setFx(OFXPOSTGLITCH_OUTLINE		, true);
        if (key == '7') myGlitch.setFx(OFXPOSTGLITCH_NOISE			, true);
        if (key == '8') myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN		, true);
        if (key == '9') myGlitch.setFx(OFXPOSTGLITCH_SWELL			, true);
        if (key == '0') myGlitch.setFx(OFXPOSTGLITCH_INVERT			, true);
        
        if (key == 'q') myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, true);
        if (key == 'w') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, true);
        if (key == 'e') myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, true);
        if (key == 'r') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, true);
        if (key == 't') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, true);
        if (key == 'y') myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, true);
        if (key == 'u') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, true);
    }
}

//--------------------------------------------------------------
void visuals::keyReleased(int key){
    
    //Glitch-switch
    {
        if (key == '1') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, false);
        if (key == '2') myGlitch.setFx(OFXPOSTGLITCH_GLOW			, false);
        if (key == '3') myGlitch.setFx(OFXPOSTGLITCH_SHAKER			, false);
        if (key == '4') myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, false);
        if (key == '5') myGlitch.setFx(OFXPOSTGLITCH_TWIST			, false);
        if (key == '6') myGlitch.setFx(OFXPOSTGLITCH_OUTLINE		, false);
        if (key == '7') myGlitch.setFx(OFXPOSTGLITCH_NOISE			, false);
        if (key == '8') myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN		, false);
        if (key == '9') myGlitch.setFx(OFXPOSTGLITCH_SWELL			, false);
        if (key == '0') myGlitch.setFx(OFXPOSTGLITCH_INVERT			, false);
        
        if (key == 'q') myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, false);
        if (key == 'w') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, false);
        if (key == 'e') myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, false);
        if (key == 'r') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, false);
        if (key == 't') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, false);
        if (key == 'y') myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, false);
        if (key == 'u') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, false);
    }
    
}

