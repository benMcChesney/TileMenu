#include "TileContent.h"
#include "Tweenzor.h"


void TileContent::setup( ) 
{
	inactiveScale = 0.48f ; 
	activeScale = 1.0f ; 
	scale = inactiveScale ;
	bHover = false ; 

	repulseLength = 115.0f ; 
	bSelected = false ; 
	rotation = 0.0f ; 
	z = 0.0f ; 
}

void TileContent::loadImage( string path ) 
{
	image.loadImage( path ) ; 
	ofRectangle imgBounds = ofRectangle( 0 , 0 , image.width , image.height ) ; 
	float cropX = (image.width/2 ) - ( bounds.width / 2 ) ; //( bounds.width /2 ) - (( image.width - bounds.width ) /2 ) ; 
	float cropY =  (image.height/2 ) - ( bounds.height / 2 ) ;  //( bounds.height/2 ) - (( image.height - bounds.height ) / 2 ) ; 
	image.crop( cropX , cropY , bounds.width , bounds.height ) ; 

	selectedRect = bounds ; 
}

void TileContent::setOrigin ( ) 
{ 
	origin = ofPoint ( bounds.x , bounds.y ) ; 
}

void TileContent::update( ) 
{
	//rotation = ofGetElapsedTimef() * 7.0f ; 
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

void TileContent::selected( ) 
{
	if ( bSelected == false )
	{
		bSelected = true ; 
		Tweenzor::add ( &rotation, rotation , 180.0f , 0.0f , 0.65f , EASE_IN_OUT_QUAD ) ; 
		Tweenzor::add( &selectedRect.height , selectedRect.height , bounds.height * 2 , 0.0f , 0.75 , EASE_OUT_QUAD ) ; 
	}
	if ( Tweenzor::getTween( &rotation ) == NULL ) 
	{
		unselected( ) ;
	}
}

void TileContent::unselected( ) 
{
	if ( bSelected == true ) 
	{
		//bSelected = false ; 
		Tweenzor::add ( &rotation, rotation , 0.0f , 0.0f , 0.65f , EASE_IN_OUT_QUAD ) ;
		Tweenzor::add( &selectedRect.height , selectedRect.height , bounds.height , 0.0f , 0.75 , EASE_OUT_QUAD ) ; 
		Tweenzor::addCompleteListener( Tweenzor::getTween ( &selectedRect.height ) , this , &TileContent::unselectedComplete  ) ; 
		Tweenzor::add( &bounds.x , bounds.x , origin.x , 0.65f , 0.75f , EASE_OUT_QUAD ) ; 
		Tweenzor::add( &bounds.y , bounds.y , origin.y , 0.65f , 0.75f , EASE_OUT_QUAD ) ; 
	}
}


void TileContent::unselectedComplete ( float * args ) 
{
	bSelected = false ; 
}

void TileContent::draw( ) 
{
	ofSetRectMode( OF_RECTMODE_CENTER ) ; 

	
	ofPushMatrix() ; 
		ofTranslate( bounds.x , bounds.y ) ; 

		ofScale ( scale , scale ) ; 
		ofRotateY( rotation ) ; 

		ofSetColor( color ) ; 
		//if ( bSelected ) 
		ofSetRectMode( OF_RECTMODE_CORNER ) ; 
		ofRect ( -selectedRect.width/2 , -bounds.height/2  , selectedRect.width , selectedRect.height ) ; 

		ofSetRectMode( OF_RECTMODE_CENTER ) ; 
		ofSetColor( 255 , 255 , 255 , 255 ) ; 
		image.draw( 0 , 0 ,  bounds.width , bounds.height ) ; 
		
		
		//ofRect( 0 , 0  , bounds.width , bounds.height ) ; 
	ofPopMatrix() ; 

	
	ofSetRectMode( OF_RECTMODE_CENTER ) ; 
	ofFill( ) ; 
	ofSetColor ( 255 , 255 , 255 , 255 ) ; 

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


