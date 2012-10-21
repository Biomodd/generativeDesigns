#include "testApp.h"

/*=============================================
METABALL CLASS
 recompiled and abstracted for biomodd [NYC4].
 Example app doesn't have that much functionality:
 move mouse to create new metaballs...
 
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

void testApp::setup(){
    ofBackground(0);
    
    for (short i = 0; i < 50; i++) {
        simpleBall tempBall;
        tempBall.pos    = ofVec2f(ofRandom(10, ofGetWidth()-10), ofRandom(10, ofGetHeight()-10));
        tempBall.size   = (int) ofRandom(20, 40);
        ofColor col;
        col.setHsb(ofRandom(255), 230, 150);
        tempBall.col = col;
        myBalls.push_back(tempBall);
    }
    
    for (short i = 0; i < 50; i++) {
        for (short j = i - 1; j >= 0; j--) {
            if (myBalls.at(i).pos.distance(myBalls.at(j).pos)<DISTANCE) {
                metaballs.addMetaball(myBalls.at(i).pos, myBalls.at(j).pos, myBalls.at(i).size, myBalls.at(j).size, DISTANCE, 1, myBalls.at(i).col, myBalls.at(j).col);
            }
        }
    }


}

//--------------------------------------------------------------
void testApp::update(){
    mouseBall.init();
    for (short i = 0; i < myBalls.size(); i++) {
        if (myBalls.at(i).pos.distance(ofVec2f(mouseX, mouseY))<DISTANCE) {
            mouseBall.addMetaball(myBalls.at(i).pos, ofVec2f(mouseX, mouseY), myBalls.at(i).size, 30, DISTANCE, 1, myBalls.at(i).col, ofColor(125,0, 125));
        }
    }

}

//--------------------------------------------------------------
void testApp::draw(){
    metaballs.draw();
    
    ofPushStyle();
    ofFill();
    for (int i = 0; i < myBalls.size(); i++) {
        ofSetColor(myBalls.at(i).col);
        ofCircle(myBalls.at(i).pos, myBalls.at(i).size);
    }
    ofPopStyle();
    
    ofPushStyle();
    mouseBall.draw();
    ofSetColor(125, 0, 125);
        ofFill();
    ofCircle(mouseX, mouseY, 30);
    ofPopStyle();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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