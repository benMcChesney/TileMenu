#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "TileContainer.h"

#define NUM_PTS 800

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

		void drawGUI( ) ; 
		ofxXmlSettings xml;

		vector<TileContainer*> tiles ; 
		TileContainer* selectedTile ; 

		void loadTileXml( ) ; 
		void saveTileXml( ) ; 
		void createRandomTile( ) ; 
		void deleteSelectedTile ( ) ; 
};

