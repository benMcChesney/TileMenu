#pragma once

#include "ofMain.h"

class TileContainer
{
public : 
	TileContainer( ) { } 
	
	ofRectangle bounds ; 
	ofColor color ; 
	
	void setup ( float x , float y , float width , float height , ofColor _color ) 
	{
		color = _color ; 
		bounds = ofRectangle( x , y , width , height ) ; 
	}

	void update ( ) 
	{

	}

	void draw ( ) 
	{
		ofSetColor ( color )  ; 
		ofSetRectMode( OF_RECTMODE_CENTER  ) ; 
		ofRect( bounds ) ; 
	}

	bool hitTest ( float _x , float _y ) 
	{
		float x = _x + bounds.width / 2 ; 
		float y = _y + bounds.height / 2 ; 
		return ( (( x > bounds.x ) && ( x < bounds.x + bounds.width )) && (( y > bounds.y ) && ( y < bounds.y + bounds.height )) ) ; 
	}
};