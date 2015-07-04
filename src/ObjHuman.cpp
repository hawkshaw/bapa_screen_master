//
//  object.cpp
//  bapa_visualization
//
//  Created by Toyama Genki on 2015/06/30.
//
//

#include "ObjHuman.h"

ObjHuman::ObjHuman(){
    radius = 40;
    bFixed = false;
}

void ObjHuman::setup(ofVec2f _position, ofVec2f _velocity){
    position = _position;
    velocity = _velocity;
}

void ObjHuman::setup(float positionX, float positionY, float velocityX, float velocityY){
    position = ofVec2f(positionX, positionY);
    velocity = ofVec2f(velocityX, velocityY);
}

void ObjHuman::setupLong(ofVec2f _position, ofVec2f _velocity, float _length){
    position = _position;
    velocity = _velocity;
    length = _length;
}

void ObjHuman::updatePos(){
    if (!bFixed) {
        position += velocity;
    }
}


void ObjHuman::update(){
    updatePos();
}


void ObjHuman::draw(){
    ofSetColor(255);
    ofCircle(position, radius);
    ofSetColor(0, 0, 255);
    ofCircle(position, radius*0.85);
}

void ObjHuman::drawLong(){
    ofSetColor(255);
    ofCircle(position, radius);
    ofRect(position.x, position.y-radius, length, radius*2);
    ofCircle(position+ofVec2f(length, 0),radius);
    ofSetColor(0, 255, 0);
    ofCircle(position, radius*0.85);
    ofRect(position.x, position.y-(radius*0.85), length, (radius*0.85)*2);
    ofCircle(position+ofVec2f(length, 0),radius*0.85);
}