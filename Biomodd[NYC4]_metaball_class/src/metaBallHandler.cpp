//
//  metaBallHandler.cpp
//  emptyExample
//
//  Created by Pieter Steyaert on 11/06/12.
//  Copyright (c) 2012 Sint Lucas Gent. All rights reserved.
//
#include "metaBallHandler.h"
#include <iostream>

metaBallHandler::metaBallHandler(){
    
}

void metaBallHandler::init(){
    for (int i = 0; i < myMetaBalls.size(); i++) {
        myMetaBalls.at(i).destroy();
    }
    myMetaBalls.clear();
}

void metaBallHandler::addMetaball(ofVec2f ball1, ofVec2f ball2, int _radius1, int _radius2, int maxDistance, float bendingScalar, ofColor ball1c, ofColor ball2c){
    myMetaBalls.push_back(metaball(ball1, ball2, _radius1, _radius2, maxDistance, bendingScalar, ball1c, ball2c));
}

void metaBallHandler::draw(){
    for (int i = 0; i < myMetaBalls.size(); i++) {
        myMetaBalls.at(i).drawMetaball();
    }
}