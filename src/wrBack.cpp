//
//  wrBack.cpp
//  oscTester
//
//  Created by Jonas Kjellberg on 3/3/14.
//
//

#include "wrBack.h"


wrBack::wrBack(){

    size = h/20;
    
}


void wrBack::update(){
    

    
}

void wrBack::draw(int pick){
    
    ofPushMatrix();
    
    switch (pick) {
        case 0:
            ofFill();
            for(int i = 0; i<w+size*10; i+= size){
                for(int o = 0; o<h; o+= size){
                    //ofDrawCone(i, o, 200, 200);
                    //ofTriangle(i, 200/2, o, i+200, o+200, i+200);
                    ofSetColor(i/10, 0, 10);
                    ofTriangle(i+size/2, o, i, o+size, i+size, o+size);
                    ofSetColor(i/10+5, 0, o/10);
                    ofTriangle(i-size/2, o, i+size/2, o, i, o+size);
                };
            };
            break;
            
        case 1:
            ofNoFill();
            ofSetColor(220, 0, 10,200);
            for(int i = 0; i<w+size; i+= size){
                for(int o = 0; o<h; o+= size){
                    ofPushMatrix();
                    ofTranslate(i,o);
                    ofRotateY(45*sin(ofGetElapsedTimef()/40+o+i)*PI);
                    ofRotateX(ofGetElapsedTimef());
                    ofDrawBox(0, 0, 0, size, size, size);
                    ofPopMatrix();
                };
            };
            break;

            
        default:
            break;
    }
    ofFill();
    ofPopMatrix();
}