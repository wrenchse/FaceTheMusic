//
//  updateThread.h
//  FaceTheMusic
//
//  Created by Jonas Kjellberg on 3/26/14.
//
//

class threadedObject : public ofThread {
    

    
    // the thread function
    void threadedFunction() {
        
        // start
        
        while(isThreadRunning()) {
            
            cam.update();
            if(cam.isFrameNew()) {
                
                // load the image
                image.setFromPixels(cam.getPixelsRef());
            }
        }
        
        // done
    }
    
    ofVideoGrabber cam;  // the cam
    ofImage image;
};
