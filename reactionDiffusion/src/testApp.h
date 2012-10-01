#pragma once

#include "ofMain.h"
#include "ofxUI.h"

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

        void fillImage();
        void drawCircle(int x, int y, float maxr);
        float dist(float x1, float y1, float x2, float y2);

        float diffusion(float** chem,int x,int y);
        float constrain(float v, float min, float max);

		int b;  // border around reaction-diffusion field
		int w;  // width
		int h;  // height

		float dt;

		float startA;   // start concentration for Activator
		float startI;   // start concentration for Inhibitor
		float diffA;    // diffusion rate for Inhibitor
		float diffI;    // diffusion rate for Activator
		float vDiffA;   // variation diffusion parameter for the Activator over the x-axis
        float vDiffI;   // variation diffusion parameter for the Inhibitor over the y-axis

        float Alpha;    // growth constant
		float vAlpha;   // vary growth constant over x-axis
		float betaMean; // mean decay parameter
		float betaNoise;// noise in decay parameter
		float vNoise;   // vary noise over y-axis

		float min, max; // maximum values for the concentrations of both chemicals

		float** A;  // A
		float** I;  // chemical B
		float** dA; // chemical A derivative
		float** dI; // chemical B derivative
		float** beta; // decay

		unsigned char* pixels;  // pixel array

		ofImage imageOut;         // output image

		bool displayBlur;
		bool mD;

		int mX, mY;

		// gui

		ofxUICanvas *gui;
		int canvasW, canvasH;
		void guiEvent(ofxUIEventArgs &e);


};
