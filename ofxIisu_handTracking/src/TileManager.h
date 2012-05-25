#pragma once

#include "ofMain.h"
#include "TileContent.h"
#include "ofxXmlSettings.h"
#include "TileMenuGlobal.h"
#include "Tweenzor.h"

class TileManager
{
	public : 
		TileManager() { } 

		void setup ( ) ;
		void setupFromXml( string xmlPath ) ;
		void input ( float x , float y ) ;
		void input ( ofVec2f pos ) ;

		void update ( ) ; 
		void draw ( ) ; 

		ofxXmlSettings tileXml ;
		vector<TileContent*> contents ; 
		void loadTileFromXml( ) ; 

		int activeTileIndex ; 
		void setNewTileActive ( int index ) ; 
		void resetTiles ( ) ; 

		int getIndexAtPoint ( float x , float y ) ; 

		TileContent * selectedTile ; 

		void setIndexAsSelected ( int index ) ; 
		ofVec2f globalSelectedPoint ; 


		float blackOutAlpha ; 

		//Close Area
		ofRectangle closeArea ; 


		bool hitTest ( float x , float y , ofRectangle r ) ; 

		void returnToMenu ( ) ; 

};