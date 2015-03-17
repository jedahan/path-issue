#include "ofApp.h"

#define MS_FOR_SELECTION 5000

void ofApp::setup(){
  int w = ofGetViewportWidth();
  int h = ofGetViewportHeight();
  ofEnableSmoothing();
  ofSetCircleResolution(128);
  circles.push_back(Circle(ofColor(0,255,255), 2 * w/6, h/2, 100));
  circles.push_back(Circle(ofColor(255,0,255), 3 * w/6, h/2, 100));
  circles.push_back(Circle(ofColor(255,255,0), 4 * w/6, h/2, 100));
  selectedColor = circles[0].c;
  shader.load("shaders/noise");
  explodeshader.load("shaders/explode");
  ofBackground(0);
  ofGetWindowPtr()->setWindowTitle("fireworks");
  startTime = endTime = -1;
}

void ofApp::update(){

}

void ofApp::draw(){
 
  for(Circle c : circles){
    ofSetColor(c.c);
    ofDrawCircle(c.x,c.y,c.r,c.r);
  }
  ofSetColor(selectedColor);
  ofDrawRectangle(mouseX-10,mouseY-10,20,20);
 
  explodeshader.begin();
  explodeshader.setUniform1f("mouseRange", 150);
  explodeshader.setUniform2f("mouse", mouseX - ofGetWidth()/2, ofGetHeight()/2-mouseY );
  explodeshader.setUniform4f("v_color", selectedColor.r/255, selectedColor.g/255, selectedColor.b/255, 1.0);
  for(ofMesh firework : fireworks){
    firework.drawVertices();
  }
  explodeshader.end();

  Circle * c = whichCircle();
  if(c){
    ofDrawCircle(c->x,c->y,c->r+20,c->r+20); 
  }
  if(endTime > 0 && ofGetElapsedTimeMillis() >= endTime){
    startTime = endTime = -1;
    ofMessage msg(ofToString("selected"));
    ofSendMessage(msg);
  }
}

void ofApp::keyPressed(int key){

}

void ofApp::keyReleased(int key){

}

void ofApp::mouseMoved(int x, int y){
  if(whichCircle()) {
    if(startTime > 0){
      startTime = ofGetElapsedTimeMillis();
      endTime = startTime + MS_FOR_SELECTION;
    }
  } else {
    startTime = endTime = -1;
  }
}

void ofApp::mouseDragged(int x, int y, int button){
}

Circle * ofApp::whichCircle() {
  for(int i=0; i < circles.size(); i++){
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

void ofApp::explode(int x, int y){
  ofMesh firework;
  for(int i=0; i<1000; i++){
    firework.addVertex(ofVec3f(x+(ofRandom(80)-40),(y+ofRandom(80)-40),0));
    firework.addColor(ofColor(selectedColor));
  }
  fireworks.push_back(firework);
}

void ofApp::mousePressed(int x, int y, int button){
  bool hitCircle = false;
  for(Circle c : circles) {
    if(pointInCircle(x,y,c)) {
      selectedColor = c.c;
      hitCircle = true;
    }
  }
  if (!hitCircle) {
    explode(x,y);
  }
}


void ofApp::mouseReleased(int x, int y, int button){
}

void ofApp::windowResized(int w, int h){
   circles[0].x = 2 * w/6;
   circles[0].y = h/2;
   circles[1].x = 3 * w/6;
   circles[1].y = h/2;
   circles[2].x = 4 * w/6;
   circles[2].y = h/2;
}

void ofApp::gotMessage(ofMessage msg) {
  cout << "Got message " + msg.message << endl;
}

void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
