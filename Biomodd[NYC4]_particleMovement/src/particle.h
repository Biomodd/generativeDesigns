/*=============================================
    PARTICLE CLASS / ORGANIC MOVEMENT
 ----------------------------------------------
 [ particle.h ]
 -----------> PIETER STEYAERT || @subtivsubtiv || 03/01/2012
 ===============================================*/

#ifndef _PARTICLECLASS
#define _PARTICLECLASS
#include "ofMain.h"
#include "SUBTIV_CONSTANTS.h"

struct particleElements {
    float radius, speed, accelerationScale, targetRandomAmount;
    short accelerationState, edgeMode;
    ofColor color;
    ofVec2f location, originalLocation, acceleration, velocity;
    bool alive;
    ofRectangle world;
};

class particleClass {

public:
	
    // -------[CONSTRUCTOR]---- 
	particleClass(); //???
	particleClass(ofVec2f loc, float radius, ofColor color = ofColor::white, ofRectangle world = ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
    
    // -------[METHODS]---- 
	void update();
	void draw();
    void invertVelocity();

    // -------[GETTERS N SETTERS]---- 
    ofVec2f getPosition();
    void setPosition(ofVec2f pos);
    ofVec2f getOriginalLocation();
    void setOriginalLocation(ofVec2f pos);
    
    float getRadius();
    void setRadius(float _radius);
    
    short getAccelerationState();
    void setAccelerationState(short _accelerationState);
    
    void setSpeed(float _speed);
    float getSpeed();
    
    void setColor(ofColor _color);
    ofColor getColor();
    
    void setAccelerationScale(float _accelerationScale);
    float getAccelerationScale();
    
    void setEdgeMode(short _edgeMode);
    short getEdgeMode();
    
    void setWorld(ofRectangle _world);
    ofRectangle getWorld();
    
    void setTargetRandomAmount(float _targetRandomAmount);
    float getTargetRandomAmount();
    
    bool getAlive();
    
	
private:

    // -------[PRIVATE METHODS]---- 
    void updateAccelerationRandom();
    void updateAccelerationTarget();
    
    void updateEdgesBounce();
    void updateEdgesKill();
    void updateEdgesEternal();
    
    // -------[GLOBAL VARIABLES]---- 
    particleElements PA;
};


#endif