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
    startTime = ofGetElapsedTimeMillis();
}

void Obj::setup(ofVec2f _position, float _velocity){
    position = _position;
    objVelocity = _velocity;
    startTime = ofGetElapsedTimeMillis();
}

void Obj::setup(float positionX, float positionY, float velocity){
    position = ofVec2f(positionX, positionY);
    objVelocity = velocity;
    startTime = ofGetElapsedTimeMillis();
}

void Obj::setupLong(ofVec2f _position, float _velocity, float _length){
    position = _position;
    objVelocity = _velocity;
    length = _length;
    startTime = ofGetElapsedTimeMillis();
}

void Obj::updatePos(){
    if (!bFixed) {
        position += velocity;
    }
}


void Obj::update(){
    //updatePos();
    float timer = ofGetElapsedTimeMillis() - startTime;
    position.x = ofGetWidth() - timer/objVelocity;
}


void Obj::draw(){
    ofSetColor(255);
    ofCircle(position, radius);
    ofSetColor(0, 0, 255);
    ofCircle(position, radius*0.85);
    ofSetColor(255);
    //ofLine(position.x,position.y-radius, position.x,position.y+radius);
}

void Obj::drawLong(){
    ofSetColor(255);
    ofCircle(position, radius);
    ofRect(position.x, position.y-radius, length, radius*2);
    ofCircle(position+ofVec2f(length, 0),radius);
    ofSetColor(0, 255, 0);
    ofCircle(position, radius*0.85);
    ofRect(position.x, position.y-(radius*0.85), length, (radius*0.85)*2);
    ofCircle(position+ofVec2f(length, 0),radius*0.85);
}

void Obj::drawBig(){
    ofSetColor(255);
    ofCircle(position, radius*1.5);
    ofSetColor(255, 0, 0);
    ofCircle(position, radius*1.5*0.85);
}

void Obj::timeReset(){
    startTime = ofGetElapsedTimeMillis();
}

void Obj::fillRed(){
    ofSetColor(255,0,0,200);
    ofCircle(position, radius);
    ofRect(position.x, position.y-radius, length, radius*2);
    ofCircle(position+ofVec2f(length, 0),radius);
}