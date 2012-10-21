#include "testApp.h"

/*=============================================
 ORGANIC MOVEMENT // simple particle class
 recompiled and abstracted for biomodd [NYC4].
 Example app doesn't have that much functionality:
 hit any key to change the velocity mode.
 Check "SUBTIV_CONSTANTS.h" for more options.
 
 Pieter Steyaert || @subtivsubtiv
 
 ----------------------------------------------
 [ DEPENDENCIES ]
 * open frameworks
 
 ----------------------------------------------
 [ CONTRIBUTORS ]
 
 -----------> Biomodd Github Portal
 [https://github.com/Biomodd]
 
 ----------------------------------------------
 -----------> BIOMODD [NYC4] || 28/09/2012
 ===============================================*/

/////////////////////////////////
//  S E T U P
////////////////////////////////

void testApp::setup(){
    ofSetFrameRate(30);

    for (int i = 0; i < 2000; i++) {
        myControllerClass.addParticles(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), ofRandom(1, 15), ofColor(ofRandom(100, 200)));
    }
    
    myControllerClass.setEdgeMode(EDGE_MODE_ETERNAL);
    myControllerClass.setCollsionMode(COLLISION_MODE_NONE);
    myControllerClass.setOriginalLocation(ofVec2f(ofGetWidth()/2, ofGetHeight()/2));
    myControllerClass.setAccelerationState(ACCELERATION_STATE_RANDOM);
    myControllerClass.setSpeed(0.4);

    renderMode = RENDERMODE_DEFAULT;
    drawMode = DRAWMODE_MESH_POINT_LINE;
        
}

/////////////////////////////////
//  U P D A T E
////////////////////////////////
void testApp::update(){

    myControllerClass.update();
    switch (renderMode) {
        case RENDERMODE_DEFAULT:
            updateDefault();
            break;
        default:
            updateDefault();
            break;
    }
}

/////////////////////////////////
//  D R A W
////////////////////////////////
void testApp::draw(){

    ofBackground(0);

    switch (renderMode) {
        case RENDERMODE_DEFAULT:
            drawDefault();
            break;
        default:
            drawDefault();
            break;
    }

    ofPushStyle();
    ofSetColor(ofColor::red);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofPoint(30, 30));
    ofPopStyle();
    
}

//////////////////////////////////////
//  C U S T O M   F U N C T I O N S 
//////////////////////////////////////


/////////////////////////////////////

void testApp::updateDefault(){
}

void testApp::drawDefault(){
    drawParticles();
}


/////////////////////////////////////



/////////////////////////////////////

void testApp::drawParticles(){
    switch (drawMode) {
        case DRAWMODE_REGULAR:
            myControllerClass.draw();
            break;
        case DRAWMODE_MESH_POINT:
            myControllerClass.drawMeshPoint();
            break;
        case DRAWMODE_MESH_POINT_LINE:
            myControllerClass.drawMeshPointLine();
            break;
        default:
            myControllerClass.draw();
            break;
    }
    
}

/////////////////////////////////
//  I / O
////////////////////////////////

void testApp::keyPressed(int key){
    myControllerClass.setAccelerationState(ACCELERATION_STATE_TARGET);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
//    myControllerClass.setOriginalLocation(ofVec2f(mouseX, mouseY));
//    myControllerClass.setAccelerationState(ACCELERATION_STATE_TARGET);

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}