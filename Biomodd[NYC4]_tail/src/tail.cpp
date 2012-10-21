

#include <iostream>
#include "tail.h"

/*=============================================
 LOUIS(e) SIMPLE TAIL CLASS
 ----------------------------------------------
 [ tail.cpp ]
 -----------> PIETER STEYAERT || @subtivsubtiv || 25/01/2012
 
 Simple way for drawing a desired and abstracted tail,
 created for LOUIS(e) master project. Modified for Biomodd[NYC4]
 ===============================================*/

tail::tail(int _vertebraLength, int _vertebraAmount){
    vertebraLength = _vertebraLength;
    vertebraAmount = _vertebraAmount;

    crinkleDensity = 0.05f;
    crinkleAmount = 0.01f;
    crinkleOffset = 20;
    startRadius = 5;
    
    waveOffset = 0.0f;
    
    tailMesh.setMode(OF_PRIMITIVE_LINES);
}



void tail::update(ofVec2f startLocation, ofColor* historyColors){
    _StartLocation = startLocation;
    updateNoiseWave();
    tailMesh.clear();

    tailCenterPos[0] = startLocation;
    ofVec2f dirToNext;
    
    for (short i = 0; i < vertebraAmount; i++) {
        if (i == 0) {
            dragSegment(i+1, tailCenterPos[i]);
           
            tailCenterPosNoise[i]=ofVec2f(0,0);
            
            tailMesh.addColor(historyColors[i%9]);
            tailMesh.addVertex(ofVec3f(tailCenterPos[0].x,tailCenterPos[0].y,0));
            tailMesh.addColor(historyColors[(i+1)%9]);       
            tailMesh.addVertex(ofVec3f(tailCenterPos[0].x,tailCenterPos[0].y,0));
            
        } else if (i < vertebraAmount-1) {
            dragSegment(i+1, tailCenterPos[i]);
            dirToNext = tailCenterPos[i]-tailCenterPos[i-1];
            dirToNext.normalize();
            dirToNext.rotate(90);
            tailCenterPosNoise[i]=tailCenterPos[i]+dirToNext*waveValues[i];
            
            int scalar;
            scalar = ofMap(i, 0, vertebraAmount, startRadius*2, 0);
            
            tailMesh.addColor(historyColors[i%9]);
            tailMesh.addVertex(ofVec3f(tailCenterPosNoise[i].x-dirToNext.x*scalar, tailCenterPosNoise[i].y-dirToNext.y*scalar,0));
            tailMesh.addColor(historyColors[(i+1)%9]);       
            tailMesh.addVertex(ofVec3f(tailCenterPosNoise[i].x+dirToNext.x*scalar, tailCenterPosNoise[i].y+dirToNext.y*scalar,0));
        } else {
            dirToNext = tailCenterPos[i]-tailCenterPos[i-1];
            dirToNext.normalize();
            dirToNext.rotate(90);
            tailCenterPosNoise[i]=tailCenterPos[i]+dirToNext*waveValues[i];
            
            int scalar;
            scalar = ofMap(i, 0, vertebraAmount, startRadius*2, 0);
            
            tailMesh.addColor(historyColors[i%9]);
            tailMesh.addVertex(ofVec3f(tailCenterPosNoise[i].x-dirToNext.x*scalar, tailCenterPosNoise[i].y-dirToNext.y*scalar,0));
            tailMesh.addColor(historyColors[(i+1)%9]);       
            tailMesh.addVertex(ofVec3f(tailCenterPosNoise[i].x+dirToNext.x*scalar, tailCenterPosNoise[i].y+dirToNext.y*scalar,0));
        }
    }
    
    for (int i = 0; i < tailMesh.getNumVertices(); i++) {
        if (i < tailMesh.getNumVertices()-1) {
            if (i < tailMesh.getNumVertices()-3) {
                tailMesh.addTriangle(i+1, i+2, i+3);     
                tailMesh.addTriangle(i, i+1, i+1);
            } else {     
                tailMesh.addTriangle(i, i+1, i+1);
            }
        }
    }
}

void tail::draw(){
    
    ofNoFill();
    tailMesh.drawWireframe();
}




void tail::dragSegment(int i, ofVec2f inPos){
    
    ofVec2f d = inPos-tailCenterPos[i];
    float angle = atan2(d.y, d.x);
    
    tailCenterPos[i].x = inPos.x - cos(angle) * vertebraLength;
    tailCenterPos[i].y = inPos.y - sin(angle) * vertebraLength ;
    
}

void tail::updateNoiseWave(){
    
    int n = vertebraAmount+1;    
    waveOffset += crinkleAmount;      // Increment y ('time')
    float xoff = waveOffset;        
    
    for (int i = 1; i < n; i++) {
        waveValues[i] = (2*ofNoise(xoff)-1)*crinkleOffset;    
        xoff+=crinkleDensity;
    }    
    
}

float tail::getRotationAngle(){
    
    ofVec2f direction = tailCenterPos[0] - tailCenterPos[3];
    direction.normalize();
    direction.scale(30);
    direction += tailCenterPos[0];
    
    ofVec2f horizontal = ofVec2f(sin(PI/2), cos(PI/2));
    horizontal.scale(30);
    horizontal += tailCenterPos[0];
    
    float angle = ofVec2f(tailCenterPos[0]-horizontal).angle(ofVec2f(tailCenterPos[0]-direction));
    return  angle;
}

int tail::getLength(){
    return vertebraLength;
}


void tail::setLength(int _length){ vertebraLength = _length; } 

void tail::setAmount(int _amount){  vertebraAmount = _amount; }

void tail::setCrinkleAmount(float _amount){ crinkleAmount = _amount;}

void tail::setCrinkleDensity(float _density){ crinkleDensity = _density;}

void tail::setCrinkleOffset(float _offset){ crinkleOffset = _offset; }

void tail::setStartRadius(float _startRadius){ startRadius =  _startRadius; }







