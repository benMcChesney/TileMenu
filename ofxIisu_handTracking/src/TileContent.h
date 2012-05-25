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

		int tileIndex ; 
		bool hitTest ( float x , float y ) ; 

		ofImage image ; 
		void loadImage( string path ) ; 

		void selected ( ) ; 
		void unselected ( ) ; 
		void unselectedComplete ( float * args ) ; 

		bool bSelected ; 
		float rotation ; 


		ofRectangle selectedRect ; 

		float z ; 
};