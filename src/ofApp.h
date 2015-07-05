#pragma once

#include "ofMain.h"
#include "Obj.h"
#include "ObjHuman.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ObjHuman.h"

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
    ofxPanel gui;
    
    vector<Obj> Objects;
    vector<Obj> longObjects;
    vector<Obj> bigObjects;
    
    vector<ObjHuman> ObjHumans;
    
    void getMessage2(ofxOscMessage m);
    void getMessage22(ofxOscMessage m);
    int velx_ave,vely_ave;

    ofxOscReceiver receiver;
    ofxOscSender sender;
    
    bool bMusicStop;
    bool bMusicPlay;
    bool bMusicReset;
    
<<<<<<< HEAD
    float startTime;
    
    float objVelocity;
=======
    vector<ObjHuman> ObjHumans;
    
    void getMessage2(ofxOscMessage m);
    void getMessage22(ofxOscMessage m);
    int velx_ave,vely_ave;
>>>>>>> 2ef1f0bfc66f5d11d3b8a61fdc9178ae7a9025ed
};
