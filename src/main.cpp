#include "ofMain.h"
#include "testApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    
    //	ofSetupOpenGL(640,480, OF_WINDOW);			// <-------- setup the GL context
    
    ofAppGLFWWindow window;
    window.setMultiDisplayFullscreen(true);
    ofSetupOpenGL(&window,800*2,600,OF_WINDOW);

	ofRunApp( new testApp());
    
}
