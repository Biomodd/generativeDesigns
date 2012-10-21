//
//  tailPath.h
//  emptyExample
//
//  Created by Pieter Steyaert on 25/01/12.
//  Copyright (c) 2012 Sint Lucas Gent. All rights reserved.
//

#ifndef emptyExample_tailPath_h
#define emptyExample_tailPath_h
#define MAXAMOUNT 20 // this is the maximum amount

#include "ofMain.h"

class tail {
    
    public:
        tail(int _vertebraLength = 5, int _vertebraAmount = 10);
        void update(ofVec2f startLocation, ofColor* historyColors);
        void draw();
        void setLength(int _length);
        void setAmount(int _amount);
        void setCrinkleDensity(float _density);
        void setCrinkleAmount(float _amount);
        void setCrinkleOffset(float _offset);
        void setStartRadius(float _startRadius);
    
    void setCrontrolNumber(int _cNr);
    float getRotationAngle();
    int getLength();

    private:
        void updateNoiseWave();
        void dragSegment(int i, ofVec2f inPos);
    
    //calculate wave
    float waveOffset;
    float waveValues[MAXAMOUNT];
    
    //global variables
    int vertebraLength; 
    int vertebraAmount;
    float crinkleDensity;
    float crinkleAmount;
    float crinkleOffset;
    float startRadius;

    
    ofVec2f tailCenterPos[MAXAMOUNT];
    ofVec2f tailCenterPosNoise[MAXAMOUNT];
    ofMesh tailMesh;
    
    ofVec2f _StartLocation;
};


#endif
