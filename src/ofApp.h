#pragma once
#include "ofMain.h"

#pragma once
#include "Circle.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void mouseMoved(int x, int y );
		void windowResized(int w, int h);
		
    bool pointInCircle(int pX, int pY, Circle c);

    vector<Circle> circles;
    Circle * whichCircle();
    ofPath line;

};
