#pragma once

#include "ofMain.h"
#include "ofImage.h"

class ofxImageSequencePlayer {
public:
	ofxImageSequencePlayer() {
	};
	void init(std::string prefix, int digits, std::string extension, int start) {
		curFrame = start;
		startFrame = start;
		fPrefix = prefix;
		fExt = extension;
		numDigits = digits;
		initialized = image.load(generateFullFilename());

		if (!initialized) {
			ofLogWarning() << "ofxImageSequencePlayer: unable to load inital image in the sequence: " << generateFullFilename();
			return;
		}

		totalFrames = 0;
		ofFile testFile;
		while (testFile.open(generateFullFilename())) {
			totalFrames++;
			curFrame++;
			testFile.close();
		}
		testFile.close();
		curFrame = startFrame;
	};

	bool loadNextFrame() {
		bool worked = image.load(generateFullFilename());
		if (worked)
			curFrame++;
		return worked;
	};

	bool loadPreviousFrame() {
		bool worked = image.load(generateFullFilename());
		if (worked)
			curFrame = curFrame > 0 ? curFrame - 1 : 0;
		return worked;
	};

	bool loadFrame(int n) {
		curFrame = startFrame + n;
		bool worked = image.load(generateFullFilename());
		if (worked)
			curFrame++;
		return worked;
	};

	int getWidth() { return image.getWidth(); }
	int getHeight() { return image.getHeight(); }
	void setImageType(int imageType) { image.setImageType((ofImageType)imageType); }
	ofImageType getImageType() { return image.getImageType(); }
	ofPixels getPixels() { return image.getPixels(); }
	ofTexture getTexture() { return image.getTexture(); }
	int getCurrentFrameNumber() { return curFrame - startFrame; }
	void setCurrentFrameNumber(int i) { curFrame = startFrame + i; }
	int getSequenceLength() { return totalFrames; }
	bool isInitialized() { return initialized; }

	string generateFullFilename() {
		std::ostringstream ss;
		ss << std::setw(numDigits) << std::setfill('0') << curFrame;
		std::string result = ss.str();
		if (result.length() > numDigits) {
			result.erase(0, result.length() - numDigits);
		}
		return fPrefix + ss.str() + fExt;
	};
	ofImage image;

private:
	bool initialized;
	int curFrame, startFrame;
	string fPrefix, fExt;
	int numDigits;
	int totalFrames;
};
