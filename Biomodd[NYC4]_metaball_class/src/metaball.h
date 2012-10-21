//
//  metaball.h
//  Simple Example
//
//  Created by Pieter Steyaert on 23/01/12.
//  Copyright (c) 2012 Sint Lucas Gent. All rights reserved.
//

#ifndef Simple_Example_metaball_h
#define Simple_Example_metaball_h
#include "ofMain.h"


class metaball {
   
public:
    // << CONSTRUCTOR >>
    metaball(ofVec2f ball1, ofVec2f ball2, int _radius1, int _radius2, int maxDistance, float bendingScalar, ofColor ball1c, ofColor ball2c);
    
    // << METHODS >>
    void addMetaball(ofVec2f ball1, ofVec2f ball2, int _radius1, int _radius2, int maxDistance, float bendingScalar);
    void drawMetaball();
    void destroy();
    
    private:
    void makeMesh(int distance);
    

    ofMesh metaMesh;

    
    
};


#endif
