#pragma once

#include "ofMain.h"
#include "Obj.h"
#include "ObjHuman.h"
#include "ofxGui.h"
#include "ofxOsc.h"

#define HOST "localhost"


class ofApp : public ofBaseApp{
    private:
        ofTrueTypeFont font;
	public:
		void setup();
		void update();
		void draw();
        void draw3d();

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
    bool bBlack;
    bool bHideGui;
    int judgeLine;
    int score;
    
    int syncScore = 0;
    
    
    ofParameter<int> length_1;
    ofParameter<int> missThr;
    ofParameter<int> scalex;//8bit
    ofParameter<int> scaley;//8bit
    ofParameter<int> scalez;//8bit
    ofParameter<int> humanscale;
    ofParameter<int> humansizeoffset;
    ofParameter<int> timelineMethod;
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
    void getMessage4(ofxOscMessage m);
    void getMessage22(ofxOscMessage m);
    int velx_ave,vely_ave;
    
    void addPoint(float x, float y, float z,float size);
    void addPoint2(float x, float y, float z,float size);
        
    //2D 関連
    bool bDraw2d;
    
    //3D CG 関連
    bool bDraw3d;
    vector <ofVec3f> points;
    vector <ofVec3f> sizes;
    vector <ofVec3f> points2;//間違ってるやつ
    vector <ofVec3f> sizes2;
    
    ofVbo vbo;
    ofShader shader;
    ofEasyCam camera;
    float camDist;
    ofTexture texture;
    
};
