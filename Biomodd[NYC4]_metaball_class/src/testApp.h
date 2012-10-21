#pragma once

#include "ofMain.h"
#include "metaBallHandler.h"

#define DISTANCE 200

class testApp : public ofBaseApp{
	public:
    typedef struct simpleBall{
		ofVec2f pos;
		int size;
        ofColor col;
	};
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    metaBallHandler metaballs;
    metaBallHandler mouseBall;

    vector<simpleBall> myBalls;
    

};
