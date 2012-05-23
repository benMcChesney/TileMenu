#pragma once


#include "ofMain.h"
#include "ofxIisu.h" 
#include "CloseIisuServer.h"
#include "Tweenzor.h" 
#include "HandCursor.h"
#include "TileManager.h"
#include "TileMenuGlobal.h"


#ifndef MOUSE_DEBUG
//iisuSDK global header (includes all iisu functionalities)
#include <SDK/iisuSDK.h>
#include <iostream>
#endif

#ifdef WIN32
#include <windows.h>
#endif

#ifndef MOUSE_DEBUG
using namespace SK;
using namespace std;
#endif


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

#ifndef MOUSE_DEBUG
		CloseIisuServer iisuServer ; 
#endif
		HandCursor hand ; 

		TileManager tileManager ; 

		void handClampSelectionHandler ( int &args ) ; 

};
