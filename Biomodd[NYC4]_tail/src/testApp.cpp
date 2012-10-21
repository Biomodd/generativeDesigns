#include "testApp.h"

/*=============================================
Tail example, abstracted from LOUISe (master project
 2012). Modified for Biomodd[NYC4]
 
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

    myTail = new tail(60, 19);
    
    for (short i = 0; i < 10; i++) {
        histCol[i] = ofColor(ofRandom(50,150));
    }
    myTail->setCrinkleOffset(10);
    myTail->setCrinkleAmount(0.005);
}
//--------------------------------------------------------------
void testApp::update(){
    myTail ->update(ofVec2f(mouseX, mouseY), histCol);


}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    myTail->draw();


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