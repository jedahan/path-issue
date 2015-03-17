#include "ofApp.h"

void ofApp::setup(){
  int w = ofGetViewportWidth();
  int h = ofGetViewportHeight();
  ofEnableSmoothing();
  ofSetCircleResolution(180);
  circles.push_back(Circle(ofColor(0,255,255), 2 * w/6, h/2, 100));
  circles.push_back(Circle(ofColor(255,0,255), 3 * w/6, h/2, 100));
  circles.push_back(Circle(ofColor(255,255,0), 4 * w/6, h/2, 100));
  line.setStrokeWidth(1);
  line.setCircleResolution(180);
}

void ofApp::update(){
  line.clear();
  Circle * s = whichCircle();
  if(s){
    ofPoint p = ofPoint(s->x,s->y);
    float r = s->r+20;
    line.moveTo(p);
    line.arc(p,r,r,0,360);
  }
}

void ofApp::draw(){
  line.draw();

  for(Circle c : circles){
    ofSetColor(c.c);
    ofDrawCircle(c.x,c.y,c.r,c.r);
  }
}

Circle * ofApp::whichCircle() {
  for(int i=0; i < (int)circles.size(); i++){
    if(pointInCircle(mouseX,mouseY,circles[i])){
      return &circles[i];
    }
  }
  return NULL;
}

bool ofApp::pointInCircle(int pX, int pY, Circle c) {
    int dx = pX - c.x;
    int dy = pY - c.y;
    return dx*dx + dy*dy <= c.r*c.r;
}

void ofApp::windowResized(int w, int h){
   circles[0].x = 2 * w/6;
   circles[0].y = h/2;
   circles[1].x = 3 * w/6;
   circles[1].y = h/2;
   circles[2].x = 4 * w/6;
   circles[2].y = h/2;
}
