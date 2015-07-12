//
//  object.h
//  bapa_visualization
//
//  Created by Toyama Genki on 2015/06/30.
//
//

#pragma once
#include "ofMain.h"


class ObjHuman {
    
public:
    ObjHuman();
    
    void setup(float positionX, float positionY,int positionZ,int _speed,int _id,int _mouseStd,int _objMissThr);
    void update();
    void draw();
    
    ofVec2f position;
    int positionz;
    int speed;
    int humanid;//動体検出時のid
    int humanStd;//平均動きからのズレ量
    int count;
    float radius;
    float length;
    int objMissThr;
};


//道オブジェクト
class ObjRoad{
public:
    ObjRoad();
    ofVec4f getLeftPos(int idx);//(leftx,lefty,leftz,alpha)
    int getIdxStart();
    int getIdxEnd();
    int getRoadWidth(int idx);//x軸方向の広がり
    void update();
    
    int offsetZ;
    int count;//
    float speed;
    int width;//描画短冊の幅
    int Ythr1;//消え始めるY閾値
    int Ythr2;//完全に消えるY閾値
};