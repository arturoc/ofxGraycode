//
//  ofxGraycode.h
//  ofxGraycode
//
//  Created by Elliot Woods on 10/11/2011.
//	http://www.kimchiandchips.com
//
#pragma once
#include "ofMain.h"

#include "ofxGraycode/Payload.h"
#include "ofxGraycode/Dataset.h"

namespace ofxGraycode {
	using namespace std;

	class BaseCodec {
	public:
		BaseCodec();
		void init(const Payload& payload);
		virtual void reset() = 0;
		int getFrame() const;
		int getFrameCount() const;
	protected:
		const Payload* payload;
		int	frame;
	};


	class Encoder : public BaseCodec {
	public:
		void reset();

		bool operator>>(ofPixels& pixels);
		bool operator>>(ofImage& image);
	};


	class Decoder : public BaseCodec, public ofBaseDraws {
	public:
		void reset();
		void clearCaptures(); ///< keep data but drop captures
		void operator<<(const ofPixels& pixels);
		void operator<<(ofBaseHasPixels& image);
		bool hasData();

		uint32_t size() const; ///< camera image size
		const vector<ofPixels>& getCaptures() const;
		const ofPixels_<uint32_t>& getData() const;
		const ofPixels& getMean() const;
		void setThreshold(uint8_t distanceThreshold);
		uint8_t getThreshold() const;
		const DataSet& getDataSet() const;

		////
		//ofBaseUpdates
		void update();
		//
		////

		////
		//ofBaseDraws
		void draw(float x,float y);
		void draw(float x,float y,float w, float h);
		float getWidth();
		float getHeight();
		//
		////

		////
		//previews
		ofImage& getCameraInProjector();
		ofImage& getProjectorInCamera();
		//
		////

		////
		//file actions
		void loadDataSet(const string filename="");
		void saveDataSet(const string filename="");
		void savePreviews();
		// 
		/////
	protected:
		void calc(); ///< this is called automatically when all frames are received
		void updatePreview();
		void updatePreviewTextures();
		///Captures is only used if this payload specifies
		///	that it is offline using isOffline()
		///Offline denotes it performs image analysis at the
		///	end of all captures rather than during captures
		vector<ofPixels> captures;

		DataSet data;
		ofImage projectorInCamera, cameraInProjector;
		bool needPreviewUpdate; ///<to be thread safe, we perform the updates later in the draw function
	};
}