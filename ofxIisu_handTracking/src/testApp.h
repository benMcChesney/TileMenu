#pragma once


//iisuSDK global header (includes all iisu functionalities)
#include <SDK/iisuSDK.h>
#include <iostream>

#ifdef WIN32
#include <windows.h>
#endif

using namespace SK;
using namespace std;

#include "ofMain.h"
#include "ofxIisu.h" 
#include "CloseIisuServer.h"
#include "Tweenzor.h" 
#include "HandCursor.h"
#include "TileManager.h"


class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();
		void exit();
		void exitEventHandler ( int &exitCode ) ; 

		void keyPressed  (int key); 
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void gotMessage(ofMessage msg);

		CloseIisuServer iisuServer ; 
		HandCursor hand ; 

		TileManager tileManager ; 

		void handClampSelectionHandler ( int &args ) ; 

};
