//
//  analysis.cpp
//  FaceTheMusic
//
//  Created by Jonas Kjellberg on 3/26/14.
//
//

#include "analysis.h"

using namespace ofxCv;

analysis::analysis(){
   
    ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
    //	fejs1.loadImage("images/fejs14.jpg");
    
    tracker.setup();
    ratios.resize(10);
    
    senderLang.setup(HOST, 57120);
    startTime = 0;
    
}


void analysis::update(ofImage fyce) {
    

            tracker.update(toCv(fyce));
            position = tracker.getPosition();
            scale = tracker.getScale();
            orientation = tracker.getOrientation();
            rotationMatrix = tracker.getRotationMatrix();

    if(tracker.getFound()) {
        
        if (thinking == false) {
            startTime = 0;
            thinking  = true;
            restart = false;
        } else {
            startTime++;
            if (startTime > 100) {
                restart = true;
                
                ofxOscMessage m;
                m.setAddress("/start");
                for(int i=0; i<7; i++)
                m.addFloatArg(ratios[i]/1.618);
                senderLang.sendMessage(m);

            }
        }
    distancesRatio();
    }
}

void analysis::draw() {
	ofSetColor(255);

	
	if(tracker.getFound()) {
    
        ofSetLineWidth(1);
	//	tracker.draw();
        
        //tracker.draw();
      //  float pp = tracker.getImagePoint(vecpoint).x;
      //  float ppp = tracker.getImagePoint(vecpoint).y;
        //cout << tracker.getImagePoint(42)<<endl;
        //ofCircle(pp, ppp, 5);
        //distancesRatio();
        
        //cout << distance<<endl;
		
		//easyCam.begin();
        ofPushMatrix();
		//ofSetupScreenOrtho(640, 480, OF_ORIENTATION_UNKNOWN, true, -1000, 1000);
//		ofTranslate(,ofGetHeight()/2);
		applyMatrix(rotationMatrix);
		
		//ofDrawAxis(scale);
        ofFill();
        ofSetColor(250, 0, 0,startTime);
		tracker.getObjectMesh().drawWireframe();
        ofPopMatrix();
		//easyCam.end();
        
       // fajscrop = fajs;
     //   float fh = (tracker.getImagePoint(8).y-tracker.getImagePoint(0).y)*2;
       // float fw = tracker.getImagePoint(16).x-tracker.getImagePoint(0).x;
        //fajscrop.crop(tracker.getImagePoint(0).x-fw*0.05, tracker.getImagePoint(0).y-fh/2,                      fw*1.1, fh*1.1);
	}
}

//void analysis::keyPressed(int key) {
//	if(key == 'r') {
//		tracker.reset();
//	} else {
//        switch (key) {
//            case '1':
//                fejs = 1;
//                fajs = fejs1;
//                break;
//            case '2':
//                fejs = 2;
//                fajs = fejs2;
//                break;
//            case '3':
//                fejs = 3;
//                fajs = fejs3;
//                break;
//            case OF_KEY_RIGHT:
//                vecpoint++;
//                cout << vecpoint << endl;
//                break;
//            case OF_KEY_LEFT:
//                vecpoint--;
//                cout << vecpoint << endl;
//                break;
//            case 'q':
//                fejs = 0;
//                break;
//            default:
//                break;
//        }
//    }
//}

void analysis::distancesRatio(){
    tracker.getObjectMesh();
    float smoother = 0.9f;
    
    ofVec3f ogon    = tracker.getObjectPoint(39)+0.5*(tracker.getObjectPoint(42) - tracker.getObjectPoint(39));
    
    ofVec3f brynMitt= tracker.getObjectPoint(21)+0.5*(tracker.getObjectPoint(22) - tracker.getObjectPoint(21));
    
    ofVec3f mittMitt= tracker.getObjectPoint(0)+0.5*(tracker.getObjectPoint(16) - tracker.getObjectPoint(0));
    
    //    ofVec3f nasan   = tracker.getObjectPoint(33)+0.5*(tracker.getObjectPoint(30) - tracker.getObjectPoint(33)); mellan tipp och underpunkt
    ofVec3f nasan   = tracker.getObjectPoint(31)+0.5*(tracker.getObjectPoint(35) - tracker.getObjectPoint(31)); // mellan näsborrarna
    //return ogon+ogon2;
    
    //ofLine(((tracker.getImagePoint(36)+tracker.getImagePoint(39))/2).x,((tracker.getImagePoint(36)+tracker.getImagePoint(39))/2).y, ((tracker.getImagePoint(42)+tracker.getImagePoint(45))/2).x,((tracker.getImagePoint(42)+tracker.getImagePoint(45))/2).y);
    
    float munTillHaka   = tracker.getObjectPoint(64).distance(tracker.getObjectPoint(8));
    float nasTippHaka   = nasan.distance(tracker.getObjectPoint(8));
    float pupTillHaka   = ogon.distance(tracker.getObjectPoint(8));
    float pupTillMun    = ogon.distance(tracker.getObjectPoint(64));
    float pupNastipp    = ogon.distance(tracker.getObjectPoint(33));
    float nasBredd      = tracker.getObjectPoint(31).distance(tracker.getObjectPoint(35))*1.48;
    float ansiktBredd   = tracker.getObjectPoint(0).distance(tracker.getObjectPoint(16));
    float ogonenBredd   = tracker.getObjectPoint(36).distance(tracker.getObjectPoint(45));
    float munBredd      = tracker.getObjectPoint(48).distance(tracker.getObjectPoint(54))*1.09;
    float nasTillMun    = tracker.getObjectPoint(33).distance(tracker.getObjectPoint(64));
    
    float brynlangdC    = tracker.getObjectPoint(21).distance(tracker.getObjectPoint(0));
    float brynlangdB    = brynMitt.distance(mittMitt);
    float brynlangdA    = sqrt(pow(brynlangdC, 2) - pow(brynlangdB, 2));
    
    //cout << ansiktBredd/(ansiktBredd-brynlangdA) << endl;
    
    //ofCircle(nasan,2);
    
    
    ratios[0] = ratios[0] * smoother +  nasTippHaka /   munTillHaka             * (1.0-smoother);
    ratios[1] = ratios[1] * smoother +  pupTillHaka  /   nasTippHaka             * (1.0-smoother);
    ratios[2] = ratios[2] * smoother +  pupTillHaka /   pupTillMun              * (1.0-smoother);
    ratios[3] = ratios[3] * smoother +  nasBredd    /   nasTillMun              * (1.0-smoother);
    ratios[4] = ratios[4] * smoother +  munBredd    /   nasBredd                * (1.0-smoother);
    ratios[5] = ratios[5] * smoother +  ansiktBredd /   ogonenBredd             * (1.0-smoother);
    ratios[6] = ratios[6] * smoother +  ansiktBredd/(ansiktBredd-brynlangdA)    * (1.0-smoother);
    
    float sum = 0;
    for(int i = 0; i< 7; i++) {
        sum = sum + abs((ratios[i]));
    };
    
    sum = (sum/7)/1.618;
    
    cout << sum << endl;
    
    //cout << ogon <<  "    v: "  << tracker.getImagePoint(39) << "     h: " << tracker.getImagePoint(42); //" << tracker.getImagePoint(30) << "  " << nasTippHaka/munTillHaka<< "   " << nasTippHaka/pupNastipp<<endl;
    //cout << "   nastipp: " << tracker.getObjectPoint(30) << "    punastipp: " << pupNastipp << endl;
    
}
