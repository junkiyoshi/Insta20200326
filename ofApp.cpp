#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();

	auto fbo_ico_sphere = ofIcoSpherePrimitive(250, 4);
	this->fbo_mesh = fbo_ico_sphere.getMesh();

	auto draw_ico_sphere = ofIcoSpherePrimitive(245, 4);
	this->draw_mesh = draw_ico_sphere.getMesh();

	this->fbo.allocate(ofGetWidth(), ofGetHeight());
	this->fbo.readToPixels(this->pixels);
	this->pixels_mat = cv::Mat(this->pixels.getHeight(), this->pixels.getWidth(), CV_8UC4, this->pixels.getData());
}
//--------------------------------------------------------------
void ofApp::update() {

	this->fbo_mesh.clearColors();
	this->draw_mesh.clearColors();

	for (int i = 0; i < this->fbo_mesh.getVertices().size(); i++) {

		auto vertex = this->fbo_mesh.getVertices()[i];
		ofColor color = ofColor(ofMap(ofNoise(glm::vec4(vertex * 0.005, vertex.z * 0.03 + ofGetFrameNum() * 0.03)), 0, 1, 39, 239));

		this->fbo_mesh.addColor(color);
		this->draw_mesh.addColor(color);
	}

	this->fbo.begin();
	ofClear(0);

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	this->fbo_mesh.draw();

	this->fbo.end();
	this->fbo.readToPixels(this->pixels);

	cv::GaussianBlur(this->pixels_mat, this->pixels_mat, cv::Size(19, 19), 29, 29);

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofFill();
	ofSetColor(255);
	ofImage draw_image;
	draw_image.setFromPixels(this->pixels);
	draw_image.draw(0, 0);

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	this->draw_mesh.draw();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}