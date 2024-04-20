#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	ofNoFill();
	ofSetLineWidth(1);
	ofSetColor(255);
	ofDrawRectangle(glm::vec2(), 600, 600);
	ofDrawRectangle(glm::vec2(), 400, 400);
	ofDrawRectangle(glm::vec2(), 200, 200);

	auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));

	ofFill();
	ofSetLineWidth(2.5);
	ofColor color;
	for (int param = 500; param < 600; param += 2) {

		color.setHsb(ofMap(param, 500, 600, 0, 255), 255, 255);
		ofSetColor(color);

		auto location = this->make_point(600, param);
		auto target_param = param + ofMap(ofNoise(600 + noise_seed.x + ofGetFrameNum() * 0.005), 0, 1, -500, 500);
		auto target = this->make_point(400, target_param);
		auto next_target_param = param + ofMap(400 + noise_seed.x + ofNoise(ofGetFrameNum() * 0.005), 0, 1, -500, 500);
		auto next_target = this->make_point(200, next_target_param);

		ofDrawLine(location, target);
		ofDrawLine(target, next_target);
		ofDrawCircle(location, 4);
		ofDrawCircle(target, 3);
		ofDrawCircle(next_target, 2);
	}

	/*
	int start = 125;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}