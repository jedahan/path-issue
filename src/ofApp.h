#pragma once
#include "ofMain.h"

#pragma once
#include "Circle.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void windowResized(int w, int h);
		
    bool pointInCircle(int pX, int pY, Circle c);
    Circle * whichCircle();

    vector<Circle> circles;
    ofPath line;

};
