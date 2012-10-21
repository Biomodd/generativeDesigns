//
//  metaBallHandler.h
//  emptyExample
//
//  Created by Pieter Steyaert on 11/06/12.
//  Copyright (c) 2012 Sint Lucas Gent. All rights reserved.
//

#ifndef emptyExample_metaBallHandler_h
#define emptyExample_metaBallHandler_h
#include "ofMain.h"
#include "metaball.h"

class metaBallHandler {
public:
    metaBallHandler();
    void init();
    void addMetaball(ofVec2f ball1, ofVec2f ball2, int _radius1, int _radius2, int maxDistance, float bendingScalar, ofColor ball1c, ofColor ball2c);
    void draw();
    
private:
    vector<metaball> myMetaBalls;
    
    
};


#endif
