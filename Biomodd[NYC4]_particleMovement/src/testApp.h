#pragma once

#include "ofMain.h"
#include "SUBTIV_CONSTANTS.h"
#include "particleControllerClass.h"



class testApp : public ofBaseApp{
	public:
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

    void loadSVG(string name);
    
    void updateDefault();
    void drawDefault();
    
    void drawParticles();
    
    // -------[GLOBALS]---- 
    short renderMode;
    short drawMode;
    particleControllerClass myControllerClass;
};
