#include "testApp.h"

/*=============================================
 MESHLINE
 recompiled and abstracted for biomodd [NYC4].
 Example app doesn't have that much functionality:
 Move the mouse to "stretch" out the line...
 
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

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0);


}

//--------------------------------------------------------------
void testApp::update(){


}

//--------------------------------------------------------------
void testApp::draw(){
    mLine.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){


}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
    pLine.addVertex(ofPoint(x,y));
            mLine.setTriangleLine(pLine, ofVec2f(1,30), 130, ofColor::gray);



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