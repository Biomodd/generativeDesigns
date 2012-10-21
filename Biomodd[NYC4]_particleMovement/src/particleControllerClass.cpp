/*=============================================
 PARTICLE CONTROLLER CLASS
 ----------------------------------------------
 [ particleControllerClass.mm ]
    -----------> PIETER STEYAERT || @subtivsubtiv || 03/01/2012
 
 This class is created to controll the particles,
 there's not that much that goes on around here,
 its more or less a middleman between the 
 testApp class en the particle class.
 Its main purpose is to keep everything clean.
 The information of every particle is saved within
 one simple container, an array of the particleControllerClass
 objects. There is no need to use a dynamic array,
 such as the <vector> class, since the x- and
 y-resolution are fixed, the amount of pixels / 
 partikels will thus never change.
 ===============================================*/

#include "particleControllerClass.h"

/////////////////////////////////
//  C O N S T R U C T O R
////////////////////////////////

particleControllerClass::particleControllerClass(){
    collisionMode = COLLISION_MODE_DOMINANT_DEFAULT;
    collisionFramerate = 2;
//    pMesh.setUsage(GL_DYNAMIC_DRAW); // make fboMesh when i've got internet
}


/////////////////////////////////
//  M E T H O D S
////////////////////////////////

void particleControllerClass::update(){
	for (int i = 0; i < particles.size(); i++) {
		particles[i].update();
	}
    
    if (ofGetFrameNum()%collisionFramerate==0) {
        for (int i = 0; i < particles.size(); i++) {
            if (particles.at(i).getAlive()==false) {
                particles.erase(particles.begin()+i);
            }
        }        
    }
    
    if (collisionMode != COLLISION_MODE_NONE) {
        if (ofGetFrameNum()%collisionFramerate==0) {
            collisionDetecting();
        }   
    }
    pMesh.clear();
    lMesh.clear();
}

void particleControllerClass::draw(){
	for (int i = 0; i < particles.size(); i++) {
		particles[i].draw();
	}	
}

void particleControllerClass::drawMeshPoint(){
    for (int i = 0; i < particles.size(); i++) {
        pMesh.addVertex(particles.at(i).getPosition());
    }
    pMesh.setMode(OF_PRIMITIVE_POINTS);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(5);
    pMesh.drawVertices();
    
}

void particleControllerClass::drawMeshPointLine(){
    for (int i = 0; i < particles.size(); i++) {
        pMesh.addVertex(particles.at(i).getPosition());
    }
    pMesh.setMode(OF_PRIMITIVE_POINTS);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(5);
    pMesh.drawVertices();
    
    float minDis = 30;
    lMesh.setMode(OF_PRIMITIVE_LINES);
    glLineWidth(1);
    
    for (int i = 0; i < particles.size(); i++) {
        for (int j = i-1; j >=0; j--) {
            if (particles.at(i).getPosition().distance(particles.at(j).getPosition())<=minDis) {
                lMesh.addVertex(particles.at(i).getPosition());
                lMesh.addColor(ofColor(255,100));
                lMesh.addVertex(particles.at(j).getPosition());
                lMesh.addColor(ofColor(255,100));
            }
        }
    }

    lMesh.draw();
    
}

void particleControllerClass::addParticles(float x, float y, float radius, ofColor color){
    addParticles(ofVec2f(x, y), radius, color);
}

void particleControllerClass::addParticles(ofVec2f loc, float radius, ofColor color){
    particles.push_back(particleClass(loc, radius, color));
}

void particleControllerClass::removeParticles(int amt){
	for (int i = 0; i < amt; i++) {
		particles.pop_back();
	}
}

void particleControllerClass::removeParticle(int index){
    particles.erase(particles.begin()+index);
}

void particleControllerClass::clearParticles(){
    particles.clear();
}

void particleControllerClass::collisionDetecting(){
    
    for (int i = 0; i < particles.size(); i++) {
        for (int j = i-1; j >=0; j--) {
            if (i!=j) {
                ofVec2f loc1, loc2, direction;
                int totalRadius = particles.at(i).getRadius()+particles.at(j).getRadius();
                int slave, master;
                
                if (particles.at(i).getRadius()>=particles.at(j).getRadius()) {
                    loc1 = particles.at(i).getPosition();
                    loc2 = particles.at(j).getPosition();    
                    master = i;
                    slave = j;
                } else {
                    loc1 = particles.at(j).getPosition();
                    loc2 = particles.at(i).getPosition();
                    master = j;
                    slave = i;
                }
                
                
                if (ofDist(loc1.x, loc1.y, loc2.x, loc2.y)<= totalRadius) {
                    
                    switch (collisionMode) {
                        case COLLISION_MODE_DEFAULT:
                            direction = loc1 - loc2;
                            direction.normalize();
                            particles.at(master).setPosition(direction+loc1);
                            
                            direction = loc2 - loc1;
                            direction.normalize();
                            particles.at(slave).setPosition(direction+loc2);
                            break;
                            
                        case COLLISION_MODE_DOMINANT_DEFAULT:
                            direction = loc2 - loc1;
                            direction.normalize();
                            particles.at(slave).setPosition(direction+loc2);
                            break;
                            
                        case COLLISION_MODE_VELINVERT:
                            particles.at(master).invertVelocity();
                            particles.at(slave).invertVelocity();
                            break;
                            
                        case COLLISION_MODE_DOMINANT_VELINVERT:
                            particles.at(slave).invertVelocity();
                            break;
                            
                        case COLLISSION_MODE_DEFAULT_AND_VELINVERT:
                            particles.at(master).invertVelocity();
                            particles.at(slave).invertVelocity();
                            
                            direction = loc1 - loc2;
                            direction.normalize();
                            particles.at(master).setPosition(direction+loc1);
                            
                            direction = loc2 - loc1;
                            direction.normalize();
                            particles.at(slave).setPosition(direction+loc2);
                            break;
                            
                        case COLLISION_MODE_DOMINANT_DEFAULT_AND_VELINVERT:
                            particles.at(slave).invertVelocity();
                            
                            direction = loc2 - loc1;
                            direction.normalize();
                            particles.at(slave).setPosition(direction+loc2);
                            break;
                            
                        default:
                            break;
                    }
                }
                
            }
        }
    }
}


/////////////////////////////////////
//  G E T T E R S -N- S E T T E R S
/////////////////////////////////////

int particleControllerClass::getAmount(){
    return particles.size();
}

/////////////////////////////////////

ofVec2f particleControllerClass::getPosition(int index){
    return particles.at(index).getPosition();
}

void particleControllerClass::setPosition(ofVec2f pos){
    for (int i = 0; i < particles.size(); i++) {
        setPosition(pos, i);
    }
}

void particleControllerClass::setPosition(ofVec2f pos, int index){
        particles.at(index).setPosition(pos);
}

void particleControllerClass::setOriginalLocation(ofVec2f pos){
    for (int i = 0; i < particles.size(); i++) {
        setOriginalLocation(pos, i);
    }
}

void particleControllerClass::setOriginalLocation(ofVec2f pos, int index){
    for (int i = 0; i < particles.size(); i++) {
        particles.at(index).setOriginalLocation(pos);
    }    
}

void particleControllerClass::setOnOriginalLocation(){
    for (int i = 0; i < particles.size(); i++) {
        particles.at(i).setPosition(particles.at(i).getOriginalLocation());
    }
}

/////////////////////////////////////

float particleControllerClass::getRadius(int index){
    return particles.at(index).getRadius();
}

void  particleControllerClass::setRadius(float _radius){
    for (int i = 0; i < particles.size(); i++) {
        setRadius(_radius, i);
    }
}

void  particleControllerClass::setRadius(float _radius, int index){
    particles.at(index).setRadius(_radius);   
}

/////////////////////////////////////

short particleControllerClass::getAccelerationState(int index){
    return particles.at(index).getAccelerationScale();
}

void particleControllerClass::setAccelerationState(short _accelerationState){
    for (int i = 0; i < particles.size(); i++) {
        setAccelerationState(_accelerationState, i);
    }
}

void particleControllerClass::setAccelerationState(short _accelerationState, int index){
    particles.at(index).setAccelerationState(_accelerationState);
}

/////////////////////////////////////

float particleControllerClass::getSpeed(int index){
    return particles.at(index).getSpeed();
}

void particleControllerClass::setSpeed(float _speed){
    for (int i = 0; i < particles.size(); i++) {
        setSpeed(_speed);
    }
}

void particleControllerClass::setSpeed(float _speed, int index){
    particles.at(index).setSpeed(_speed);
}

/////////////////////////////////////

ofColor particleControllerClass::getColor(int index){
    return particles.at(index).getColor();
}

void particleControllerClass::setColor(ofColor _color){
    for (int i = 0; i < particles.size(); i++) {
        setColor(_color, i);
    }
}

void particleControllerClass::setColor(ofColor _color, int index){
    particles.at(index).setColor(_color);
}

/////////////////////////////////////

float particleControllerClass::getAccelerationScale(int index){
    return particles.at(index).getAccelerationScale();
}

void particleControllerClass::setAccelerationScale(float _accelerationScale){
    for (int i = 0; i < particles.size(); i++) {
        setAccelerationScale(_accelerationScale, i);
    }
}

void particleControllerClass::setAccelerationScale(float _accelerationScale, int index){
    particles.at(index).setAccelerationScale(_accelerationScale);
}

/////////////////////////////////////

short particleControllerClass::getEdgeMode(int index){
    return particles.at(index).getEdgeMode();
}

void particleControllerClass::setEdgeMode(short _edgeMode){
    for (int i = 0; i < particles.size(); i++) {
        setEdgeMode(_edgeMode, i);
    }
}

void particleControllerClass::setEdgeMode(short _edgeMode, int index){
    particles.at(index).setEdgeMode(_edgeMode);
}

/////////////////////////////////////

ofRectangle particleControllerClass::getWorld(int index){
    return particles.at(index).getWorld();
}

void particleControllerClass::setWorld(ofRectangle _world){
    for (int i = 0; i < particles.size(); i++) {
        setWorld(_world, i);
    }
}

void particleControllerClass::setWorld(ofRectangle _world, int index){
    particles.at(index).setWorld(_world);
}

/////////////////////////////////////

short particleControllerClass::getCollisionMode(){
    return collisionMode;
}

void particleControllerClass::setCollsionMode(short _collsionMode){
    collisionMode = _collsionMode; 
}

short particleControllerClass::getCollisionFrameRate(){
    return collisionFramerate;
}

void particleControllerClass::setCollisionFrameRate(short _collisionFrameRate){
    collisionFramerate = _collisionFrameRate;
}

/////////////////////////////////////

float particleControllerClass::getTargetRandomAmount(int index){
    return particles.at(index).getTargetRandomAmount();
}

void particleControllerClass::setTargetRandomAmount(float _amount){
    for (int i = 0; i < particles.size(); i++) {
        setTargetRandomAmount(_amount, i);
    }
}

void particleControllerClass::setTargetRandomAmount(float _amount, int index){
    particles.at(index).setTargetRandomAmount(_amount);
}








