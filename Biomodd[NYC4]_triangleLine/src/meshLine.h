

#ifndef emptyExample_meshLine_h
#define emptyExample_meshLine_h
#include "ofMain.h"


class meshLine {

public:
    // << CONSTRUCTOR >>
    meshLine();
    
    // << METHODS >>
    void setTriangleLine(ofPolyline, ofVec2f offset, int spacing, ofColor orgCol);
    void draw(ofColor currentCol = ofColor::white, bool setcolor=false);


    
private:
    // << PRIVATE METHODS >>
    ofMesh generateTriangleLine(ofPolyline polyline, ofVec2f offset, int spacing, ofColor orgCol);
    ofMesh transitionizeMesh(int counter, int max);
    
    // << GLOBALS >>
    ofVboMesh myMeshLine;
};


#endif
