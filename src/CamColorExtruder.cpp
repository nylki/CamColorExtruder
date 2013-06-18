//by Tom Brewe
//licence: GPL3, see licence-gpl.txt
#include "CamColorExtruder.h"

//--------------------------------------------------------------
void testApp::setup(){
	grabber.initGrabber(120, 90);
	ofSetFrameRate(20);
	
	grabber.update();
	//ofSetVerticalSync(true);
	
	ofSetGlobalAmbientColor(ofColor(255,255,255));
	
	//light.setSpecularColor(ofColor(255,255,255));
	light.setPointLight();
	ofSetSmoothLighting(true);
	
	red = true;
	green = false;
	blue = false;
	x = false;
	cursorPosition = ofPoint(0,0);

	globalRotation.set(0,0,0);
	ofColor curCursorColor;
	
	//rotate around center
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofEnableSmoothing();
	

	finder.setup("haarcascade_frontalface_default.xml");
	curCursorColor = nil;

	
	
}

//--------------------------------------------------------------
void testApp::update(){
	grabber.update();
	sphereSize = (ofGetWindowWidth() / grabber.width);
	if(grabber.isFrameNew()){
		camPixels = grabber.getPixelsRef();
		camImage.setFromPixels(camPixels);
		
		
	}
}

//--------------------------------------------------------------
void testApp::draw(){

	
	
	globalRotation += ofVec3f(5.5, 4.3, 8.9);


	ofBackground(128);

	int index,j;
	int w,h;
	ofColor c;
	j=0;
	
 
	light.enable();
	light.setPosition(mouseX, mouseY, 100);





	for(w=0; w<camImage.width; w++){
		for(h=0; h<camImage.height-1; h++){
			
			//*3 because of rgb
			index = (grabber.width * h) + (w * 3);

			c = camImage.getColor(w, h);
			//c = ofColor(camPixels[index], camPixels[index+1], camPixels[index+2]);
			
			
			//set the color of the circle to the color of the current pixel
			ofSetColor(c);
			ofFill();
			
			//adjust size for red, green or blue pixels
			float size, z;
			z=0;
			size = sphereSize;
			
			if(red && (c.r - (c.g + c.b)/2) > 20){
				//printf("red");
				size = size * c.r/60;
				z = z + c.r/2;
			}
			
			if(green && (c.g - (c.b + c.r)/2) > 30){
				//printf("green");
				size = size * c.g / 60;
				z = z + c.g/2;
			}
			
			if(blue && (c.b - (c.r + c.g)/2) > 30){
				//printf("blue");
				size = size * c.b/60;
				z = z + c.b/2;
			}
			
			
			if(!red && !blue && !green && !x) {
				size = sphereSize;
				z = c.getBrightness()/100;
			}
			
			if(x && curCursorColor != nil){
				int difference;
				//using hue and lightness to see if pixels are similiar
				difference = (abs(c.getHue() - curCursorColor.getHue()) + abs(c.getLightness() - curCursorColor.getLightness())/2);
				//printf("%d\n", difference);
				if(difference < 25){
					size = sphereSize*2;
					z = 150;
				}
			}
				
			

			ofPushMatrix();
			ofTranslate(w*sphereSize, h*sphereSize);
			
			ofRotateY(globalRotation.x);
			ofRotateX(globalRotation.y);
			ofRotateZ(globalRotation.z);
			//ofSphere(w*size, h*size, -0.9 * c.getBrightness(), size/2);
			ofBox(0, 0, z, size*0.7);
			//ofCircle(0, 0, size*0.5);
			ofPopMatrix();
			}
		}
	
	//draw color indicator
	if(dragged && x){
		curCursorColor = camImage.getColor(mouseX/sphereSize, mouseY/sphereSize);
		ofEnableAlphaBlending();
		ofSetColor(curCursorColor, 160);
		ofFill();
		ofCircle(mouseX, mouseY, 15);
		ofDisableAlphaBlending();
	}

	
	//find faces
	//finder.findHaarObjects(camImage);
	//printf("amount of faces: %d\n", finder.blobs.size());
	
	//camImage.draw(0, 0);
	//ofSetColor(255);
	//ofFill();
	/*for(int i = 0; i < finder.blobs.size(); i++) {
		ofRectangle bounding = finder.blobs[i].boundingRect;
		ofRect(bounding.getCenter() * sphereSize, (bounding.width * sphereSize) / 2, (bounding.height * sphereSize) / 2);
	}*/
	 
 

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	switch ((char) key){
		case 'r': red = !red; break;
		case 'g': green = !green; break;
		case 'b': blue = !blue; break;
		case 'x': x = !x; break;
	}

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	dragged = true;

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	dragged = true;
	cursorPosition.set((int) x, (int) y);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	dragged = false;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}