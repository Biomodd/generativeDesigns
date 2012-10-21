/*=============================================
 PARTICLE CONTROLLER CLASS
 ----------------------------------------------
 [ particleControllerClass.h]
 -----------> PIETER STEYAERT || @subtivsubtiv|| 03/01/2012
 ===============================================*/

#ifndef PARTICLE_CONTROLLER
#define PARTICLE_CONTROLLER
#include "ofMain.h"
#include "particle.h"
#include "SUBTIV_CONSTANTS.h"

class particleControllerClass {
	
public:
    // -------[CONSTRUCTOR]----
	particleControllerClass();
    
    // -------[METHODS]---- 
	void update();
	void draw();
    void drawMeshPoint();
    void drawMeshPointLine();
    
	void addParticles(float x, float y, float radius, ofColor color);
    void addParticles(ofVec2f loc, float radius, ofColor color);
//    	particleClass(ofVec2f loc, float radius, ofColor _colorC);
	void removeParticles(int amt);
    void removeParticle(int index);
    void clearParticles();
    
    void collisionDetecting();
    
    // -------[GETTERS N SETTERS]----
    int getAmount();
    
    ofVec2f getPosition(int index);
    void setPosition(ofVec2f pos);
    void setPosition(ofVec2f pos, int index);
    void setOriginalLocation(ofVec2f pos);
    void setOriginalLocation(ofVec2f pos, int index);
    void setOnOriginalLocation();
    
    float getRadius(int index);
    void  setRadius(float _radius);
    void  setRadius(float _radius, int index);
    
    short getAccelerationState(int index);
    void setAccelerationState(short _accelerationState);
    void setAccelerationState(short _accelerationState, int index);

    float getSpeed(int index);    
    void setSpeed(float _speed);
    void setSpeed(float _speed, int index);
    
    ofColor getColor(int index);
    void setColor(ofColor _color);
    void setColor(ofColor _color, int index);
    
    float getAccelerationScale(int index);
    void setAccelerationScale(float _accelerationScale);
    void setAccelerationScale(float _accelerationScale, int index);
    
    short getEdgeMode(int index);
    void setEdgeMode(short _edgeMode);
    void setEdgeMode(short _edgeMode, int index);
    
    ofRectangle getWorld(int index);
    void setWorld(ofRectangle _world);
    void setWorld(ofRectangle _world, int index);
    
    short getCollisionMode();
    void setCollsionMode(short _collisionMode);
    
    short getCollisionFrameRate();
    void setCollisionFrameRate(short _collisionFrameRate);
    
    float getTargetRandomAmount(int index);
    void setTargetRandomAmount(float _amount);
    void setTargetRandomAmount(float _amount, int index);
    
	
	
private:
    
    // -------[GLOBALS]----
    vector<particleClass> particles;
    short collisionMode;
    short   collisionFramerate;
    ofMesh pMesh;
    ofMesh lMesh;
};

#endif