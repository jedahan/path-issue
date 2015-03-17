#pragma once
#include "ofMain.h"

#pragma once
#include "Circle.h"

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
    void explode(int x, int y);
		
    vector<Circle> circles;
    bool pointInCircle(int pX, int pY, Circle c);
    Circle * whichCircle();
    ofColor selectedColor;
    ofShader shader, explodeshader;
    ofPolyline line;
    vector<ofMesh> fireworks;

    bool select;
    float startTime;
    float endTime;
};
