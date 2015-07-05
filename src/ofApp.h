#pragma once

#include "ofMain.h"
#include "Obj.h"
#include "ObjHuman.h"
#include "ofxGui.h"
#include "ofxOsc.h"

#define HOST "localhost"


class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofImage img;
    ofVideoGrabber grabber;
    bool bHideImage;
    bool bHideGui;
    int judgeLine;
    int score;
    
    ofParameter<int> length_1;
    ofParameter<int> missThr;
    ofxPanel gui;
    
    void valChanged(int &val);

    vector<Obj> Objects;
    vector<Obj> longObjects;
    vector<Obj> bigObjects;
    

    ofxOscReceiver receiver;
    ofxOscSender sender;

    
    bool bMusicStop;
    bool bMusicPlay;
    bool bMusicReset;
    
    float startTime;
    
    float objVelocity;
    vector<ObjHuman> ObjHumans;
    
    void getMessage2(ofxOscMessage m);
    void getMessage22(ofxOscMessage m);
    int velx_ave,vely_ave;
};
