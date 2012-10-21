/*=============================================
    PARTICLE CLASS / ORGANIC MOVEMENT
 ----------------------------------------------
 [ particle.mm ]
 -----------> PIETER STEYAERT || @subtivsubtiv || 03/01/2012
 
 The particle class contains all the information
 for every individual particle, it contains
 the original position of the pixel, the current
 position of a pixel, the current acceleration 
 and velocity of the particle, as well as the 
 brightness and color of the original pixel.
 
 This class does also perform the movement
 that a particle makes, based on the location, 
 velocity and acceleration. Whenever a pixel
 hits a boundary it will bounce in the opposite 
 direction.
 
 It also holds a simple draw-function, 
 that can be used for debugging.
 ===============================================*/

#include "particle.h"

/////////////////////////////////////
//  C O N S T R U C T O R
/////////////////////////////////////

particleClass::particleClass(){ // constructor 1
}

particleClass::particleClass(ofVec2f loc, float radius, ofColor color, ofRectangle world){ // constructor 2
    
	PA.location = loc;
    PA.originalLocation = loc;
    PA.acceleration.set(ofRandom(-1, 1), ofRandom(-1, 1));
    PA.velocity.set(0, 0);
    
    PA.accelerationState = ACCELERATION_STATE_STATIC;   // set default acceleration state
    PA.speed = 1;                   // set default speed
    PA.accelerationScale = 0.02;
    PA.targetRandomAmount = 0.15;
    
    PA.radius = radius;
    
    PA.alive = true;
    PA.world = world;
    
    PA.color = color;
    
    PA.edgeMode = EDGE_MODE_ETERNAL;
}


/////////////////////////////////////
//  M E T H O D S
/////////////////////////////////////

void particleClass::update(){ 
// calculate the velocity, acceleration and position of the particle
    

    
    switch (PA.accelerationState) {
        case ACCELERATION_STATE_RANDOM:
            updateAccelerationRandom();
            break;
        case ACCELERATION_STATE_TARGET:
            updateAccelerationTarget();
            break;
        default:
            break;
    }

    switch (PA.edgeMode) {
        case EDGE_MODE_BOUNCE:
            updateEdgesBounce();
            break;
        case EDGE_MODE_ETERNAL:
            updateEdgesEternal();
            break;
        case EDGE_MODE_KILL:
            updateEdgesKill();
            break;
        default:
            break;
    }
}

void particleClass::draw(){
    ofPushMatrix();
    ofTranslate(PA.location.x, PA.location.y);
	ofSetColor(0);
    ofCircle(0, 0, PA.radius);
    ofSetColor(255);
    ofCircle(0, 0, PA.radius*0.9);
    ofPopMatrix();
}

void particleClass::invertVelocity(){
    PA.velocity.x *= -1;
    PA.velocity.y *= -1;
}

/////////////////////////////////////
//  P R I V A T E   M E T H O D S
/////////////////////////////////////

void particleClass::updateAccelerationRandom(){
    
    PA.acceleration.set(ofRandom(-1,1), ofRandom(-1,1));
    PA.acceleration.normalize();
    PA.acceleration.scale(PA.accelerationScale);
    PA.velocity += PA.acceleration;
    PA.velocity.limit(PA.speed);
    PA.location += PA.velocity;
}

void particleClass::updateAccelerationTarget(){
    
    ofVec2f direction = PA.originalLocation-PA.location;
    PA.acceleration = direction;
    PA.acceleration.normalize();
    PA.acceleration.scale(PA.accelerationScale);
    PA.velocity += PA.acceleration;
    PA.velocity += ofVec2f(ofRandom(-PA.targetRandomAmount, PA.targetRandomAmount), 
                           ofRandom(-PA.targetRandomAmount, PA.targetRandomAmount));
    PA.velocity.limit(PA.speed);
    PA.location += PA.velocity;   
}

/////////////////////////////////////

void particleClass::updateEdgesBounce(){
    //makes particles bounce back by multiplying its velocity with -1.
    
    if (PA.location.x < PA.world.x + PA.radius) {
        PA.velocity.x *= -1;  
        PA.location.x = PA.world.x + PA.radius; 
    }
    
    if (PA.location.x > PA.world.width - PA.radius) { 
        PA.velocity.x *= -1; 
        PA.location.x = PA.world.width - PA.radius;
    }
    
    if (PA.location.y < PA.world.y + PA.radius) { 
        PA.velocity.y *= -1; 
        PA.location.y = PA.world.y + PA.radius;
    }
    
    if (PA.location.y > PA.world.height - PA.radius) { 
        PA.velocity.y *= -1; 
        PA.location.y = PA.world.height - PA.radius;
        
    }
}

void particleClass::updateEdgesKill(){
    if (PA.location.x < PA.world.x + PA.radius) {
        PA.alive = false;
    }
    
    if (PA.location.x > PA.world.width - PA.radius) { 
        PA.alive = false;
    }
    
    if (PA.location.y < PA.world.y + PA.radius) { 
        PA.alive = false;
    }
    
    if (PA.location.y > PA.world.height - PA.radius) { 
        PA.alive = false;
    }

}

void particleClass::updateEdgesEternal(){
    if (PA.location.x < PA.world.x - PA.radius/2) {
        PA.location.x = PA.world.width + PA.radius/2;
    }
    
    if (PA.location.x > PA.world.width + PA.radius/2) { 
        PA.location.x = PA.world.x - PA.radius/2;
    }
    
    if (PA.location.y < PA.world.y - PA.radius/2) { 
        PA.location.y = PA.world.height + PA.radius/2;
    }
    
    if (PA.location.y > PA.world.height + PA.radius/2) { 
        PA.location.y = PA.world.y - PA.radius/2;
    }

}


/////////////////////////////////////
//  G E T T E R S  N  S E T T E R S
/////////////////////////////////////

ofVec2f particleClass::getPosition(){
    return PA.location;
}

void particleClass::setPosition(ofVec2f pos){
    PA.location = pos;
}

ofVec2f particleClass::getOriginalLocation(){
    return PA.originalLocation;
}

void particleClass::setOriginalLocation(ofVec2f pos){
    PA.originalLocation = pos;
}

////////////////////////////////////

float particleClass::getRadius(){
    return PA.radius;
}

void particleClass::setRadius(float _radius){
    PA.radius = _radius;
}

////////////////////////////////////

void particleClass::setAccelerationState(short _accelerationState){
    PA.accelerationState = _accelerationState;
}

short particleClass::getAccelerationState(){
    return PA.accelerationState;
}

////////////////////////////////////

ofColor particleClass::getColor(){
    return PA.color;
}

void particleClass::setColor(ofColor _color){
    PA.color = _color;
}

////////////////////////////////////

void particleClass::setSpeed(float _speed){
    PA.speed = _speed;
}

float particleClass::getSpeed(){
    return PA.speed;
}

////////////////////////////////////

void particleClass::setAccelerationScale(float _accelerationScale){
    PA.accelerationScale = _accelerationScale;
}

float particleClass::getAccelerationScale(){
    return PA.accelerationScale;
}

////////////////////////////////////

void particleClass::setEdgeMode(short _edgeMode){
    PA.edgeMode = _edgeMode;
}

short particleClass::getEdgeMode(){
    return PA.edgeMode;
}

////////////////////////////////////

void particleClass::setWorld(ofRectangle _world){
    PA.world = _world;
}

ofRectangle particleClass::getWorld(){
    return PA.world;
}

////////////////////////////////////

void particleClass::setTargetRandomAmount(float _targetRandomAmount){
    PA.targetRandomAmount = _targetRandomAmount;
}

float particleClass::getTargetRandomAmount(){
    return PA.targetRandomAmount;
}

////////////////////////////////////

bool particleClass::getAlive(){
    return PA.alive;
}



