#include "TileContent.h"
#include "Tweenzor.h"


void TileContent::setup( ) 
{
	inactiveScale = 0.85f ; 
	activeScale = 2.0f ; 
	scale = inactiveScale ;
	bHover = false ; 

	repulseLength = 100.0f ; 
}

void TileContent::setOrigin ( ) 
{ 
	origin = ofPoint ( bounds.x , bounds.y ) ; 
}

void TileContent::update( ) 
{

}

void TileContent::inputOver ( ) 
{
	//First time active
	if ( bHover == false ) 
	{
		cout << "input Over!" << endl ; 
		bHover = true ; 
		Tweenzor::add ( &scale , scale ,activeScale , 0.0f , 0.45 , EASE_OUT_QUAD ) ; 
	}
	//else	
	//	cout << "input Over! bHover == true " << endl ; 
}

void TileContent::inputOut ( ) 
{
	if ( bHover == true ) 
	{
		cout << "input Out! " << endl ; 
		bHover = false ; 
		Tweenzor::add ( &scale , scale , inactiveScale , 0.0f , 0.45 , EASE_OUT_QUAD ) ; 
	}
//	else
//		cout << "input Out! bHover == true " << endl ; 
}

void TileContent::draw( ) 
{
	ofSetRectMode( OF_RECTMODE_CENTER ) ; 
	ofSetColor( color ) ; 
	ofPushMatrix() ; 
		ofTranslate( bounds.x , bounds.y ) ; 
		ofScale ( scale , scale ) ; 
		ofRect( 0 , 0  , bounds.width , bounds.height ) ; 
	ofPopMatrix() ; 

//	ofSetColor ( 0 , 255 , 255 ) ; 
//	ofCircle( origin, 25 ) ; 
}

bool TileContent::hitTest ( float _x , float _y )
{
	int w = bounds.width * scale ; 
	int h = bounds.height * scale ; 
	float x =  _x + w / 2.0f ; 
	float y =  _y + h  / 2.0f ; 
	return ( ( x > bounds.x ) && ( x < bounds.x + w ) ) && ( ( y > bounds.y ) && ( y < bounds.y + h )) ; 
}

void TileContent::startRepulse( ofPoint pos ) 
{
	//Seek or repulse
	ofPoint diff = origin - pos  ;
	//Create a length of 1
	diff.normalize() ; 
	//Then extend it our repulseDistance
	diff *= repulseLength ; 
	//float angle = pos.angle( origin ) ; 
	
	Tweenzor::add( &bounds.x , bounds.x , origin.x + diff.x , 0.0f , 0.45 , EASE_OUT_QUAD ) ; 
	Tweenzor::add( &bounds.y , bounds.y , origin.y + diff.y , 0.0f , 0.45 , EASE_OUT_QUAD ) ; 
}

void TileContent::endRepulse( ) 
{
	Tweenzor::add( &bounds.x , bounds.x , origin.x , 0.025f , 0.45 , EASE_OUT_QUAD ) ; 
	Tweenzor::add( &bounds.y , bounds.y , origin.y , 0.025f , 0.45 , EASE_OUT_QUAD ) ; 
}


