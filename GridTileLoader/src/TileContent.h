#pragma once


#include "ofMain.h"

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
};