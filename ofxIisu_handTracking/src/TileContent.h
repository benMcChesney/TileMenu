#pragma once


#include "ofMain.h"
#include "TileMenuGlobal.h"

class TileContent
{
	public :
		TileContent( ) { }

		ofRectangle bounds ; 
		ofColor color ; 

		void setup ( ) ; 
		void update ( ) ; 
		void draw ( ) ; 

		float scale ; 
		float inactiveScale ; 
		float activeScale ; 

		bool bHover ;
		void inputOver( ) ; 
		void inputOut( ) ;  

		ofPoint origin ; 
		void setOrigin ( ) ; 

		void startRepulse( ofPoint pos ) ; 
		ofPoint repulse ; 
		float repulseLength ; 

		void endRepulse( ) ; 

		bool hitTest ( float x , float y ) ; 

		ofImage image ; 
		void loadImage( string path ) ; 

		void selected ( ) ; 
		void unselected ( ) ; 

		bool bSelected ; 
		float rotation ; 
};