//
//  object.cpp
//  bapa_visualization
//
//  Created by Toyama Genki on 2015/06/30.
//
//

#include "Obj.h"

Obj::Obj(){
    radius = 40;
    bFixed = false;
}

void Obj::setup(ofVec2f _position, ofVec2f _velocity){
    position = _position;
    velocity = _velocity;
}

void Obj::setup(float positionX, float positionY, float velocityX, float velocityY){
    position = ofVec2f(positionX, positionY);
    velocity = ofVec2f(velocityX, velocityY);
}

void Obj::updatePos(){
    if (!bFixed) {
        position += velocity;
    }
}


void Obj::update(){
    updatePos();
}


void Obj::draw(){
    ofSetColor(255);
    ofCircle(position, radius);
    ofSetColor(0, 0, 255);
    ofCircle(position, radius*0.85);
}