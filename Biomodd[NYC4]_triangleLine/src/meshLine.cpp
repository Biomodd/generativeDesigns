
#include "meshLine.h"

/*=================================================================
 
 <<<DIGITAL ORGANISM || COMMENSAL FOR A HABITAT>>>
 ------> Pieter Steyaert |  meshline || @subtivsubtiv
 ------------------------------------------------------------------
 Just a little class that's being used to generate the aethetics for
 the skeleton-structure and the growing elements.
 
 ==================================================================*/


///////////////////////////////////////////
//	CONSTRUCTOR
///////////////////////////////////////////

meshLine::meshLine(){ }


///////////////////////////////////////////
//	METHODS
///////////////////////////////////////////

void meshLine::setTriangleLine(ofPolyline polyline, ofVec2f offset, int spacing, ofColor orgCol){
    myMeshLine = generateTriangleLine(polyline, offset, spacing, orgCol);
    myMeshLine.setUsage(GL_DYNAMIC_DRAW);
}

void meshLine::draw(ofColor currentCol, bool setcolor){
    if (setcolor==true){
        myMeshLine.setColor(0, currentCol);
    }
    myMeshLine.draw();
}


///////////////////////////////////////////
//	PRIVATE METHODS
///////////////////////////////////////////

ofMesh meshLine::generateTriangleLine(ofPolyline polyline, ofVec2f offset, int spacing, ofColor orgCol){

    polyline = polyline.getResampledByCount(spacing);
    ofMesh returnMesh;
    returnMesh.addVertex(polyline.getVertices().front());
    for (int i = 1; i < polyline.size(); i++) {
        ofVec2f vec1 = polyline.getVertices().at(i);
        ofVec2f vec2 = polyline.getVertices().at(i-1);
        ofVec2f vec3;
        
        
        for (short j = 0; j < 2; j++) {
            
            vec3 = vec2 - vec1;
            vec3.normalize();
            if (j == 0)
                vec3.rotate(90);
            else 
                vec3.rotate(-90);
            vec3.scale(ofRandom(offset.x, offset.y));
            vec3 += vec1;
            returnMesh.addVertex(ofVec3f(vec3.x, vec3.y, ofRandom(-offset.y,offset.y)));
        }
    }

    
    ofMesh tempMesh;
    int numMeshPoints = returnMesh.getVertices().size();
    
    for (short i = 0; i < numMeshPoints-2; i++) {
    
        ofColor c1 = orgCol;
        c1.setBrightness(ofRandom(50,150));
        
        
        for (short j = 0; j < 3; j++) {
            tempMesh.addColor(c1);
            // this seems kinda weird, we need to get: 0,1,2,1,2,3,2,3,4,3,4,5...
            tempMesh.addVertex(returnMesh.getVertices().at(((i*3+j)%3)+i));
        }
    }    
    returnMesh = tempMesh;
    tempMesh.clear();
    // NAN STUFF
    for (int i = 0; i < returnMesh.getNumVertices(); i++) {
        if (returnMesh.getVertex(i).x != returnMesh.getVertex(i).x) {
            returnMesh.setVertex(i, ofVec3f(0,0,0));
        }
    }
    
    return returnMesh;
}

ofMesh meshLine::transitionizeMesh(int counter, int max){
    ofMesh returnMesh = myMeshLine;

    for (int i = 0; i < returnMesh.getColors().size(); i++) {
        ofColor c1 = returnMesh.getColors().at(i);
        float calculateBrightness = ofMap(counter, 0, max, 0, c1.a);
        c1 = ofColor(c1.r, c1.g,c1.b, calculateBrightness);
        returnMesh.setColor(i, c1);
    }
    

    return returnMesh;
}










