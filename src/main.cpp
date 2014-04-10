#include "ofMain.h"
#include "testApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    
    //	ofSetupOpenGL(640,480, OF_WINDOW);			// <-------- setup the GL context
    
    ofAppGLFWWindow window;
    window.setMultiDisplayFullscreen(true);
    ofSetupOpenGL(&window,1024*2,768,OF_FULLSCREEN);

	ofRunApp( new testApp());
    
}
