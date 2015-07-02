//
//  object_long.cpp
//  bapa_visualization
//
//  Created by Toyama Genki on 2015/06/30.
//
//

#include "longObj.h"

longObj::longObj(){
    radius = 40;
    bFixed = false;
}

void longObj::setup(ofVec2f _position, ofVec2f _velocity, float insideWidth){
    position = _position;
    velocity = _velocity;
    width = insideWidth;
}

void longObj::setup(float positionX, float positionY, float velocityX, float velocityY,
                    float insideWidth){
    position = ofVec2f(positionX, positionY);
    velocity = ofVec2f(velocityX, velocityY);
    width = insideWidth;
}

void longObj::updatePos(){
    if (!bFixed) {
        position += velocity;
    }
}


void longObj::update(){
    updatePos();
}


void longObj::draw(){
    ofSetColor(255);
    ofCircle(position, radius);
    ofRect(position.x, position.y-radius, width, radius*2);
    ofCircle(position+ofVec2f(width, 0),radius);
    ofSetColor(0, 255, 0);
    ofCircle(position, radius*0.85);
    ofRect(position.x, position.y-(radius*0.85), width, (radius*0.85)*2);
    ofCircle(position+ofVec2f(width, 0),radius*0.85);


}