#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofBackground( 15 ) ; 
	loadTileFromXml( ) ;
	activeTileIndex = -2 ; 
	Tweenzor::init( ) ; 

	ofSetVerticalSync( true ) ; 
	ofSetFrameRate( 60 ) ; 
}

void testApp::setNewTileActive( int index ) 
{
	//If the last active tile EXISTS
	if ( activeTileIndex > -1 ) 
	{
		cout << "lastActive tile " << activeTileIndex << endl ; 
		//Transition out the last active tile
		contents[activeTileIndex]->inputOut( ) ; 
	}
	//Set the new index
	activeTileIndex = index ; 
	contents[index]->inputOver( ) ; 

	ofPoint repulse = contents[index]->origin ; 
	for ( int i = 0 ; i < contents.size() ; i++ ) 
	{
		if ( i != activeTileIndex ) 
		{
			contents[i]->startRepulse( repulse ) ; 
		}
	}		
}

void testApp::resetTiles( ) 
{
	contents[activeTileIndex]->inputOut( ) ; 
	activeTileIndex = -1 ; 

	for ( int i = 0 ; i < contents.size() ; i++ ) 
	{
		if ( i != activeTileIndex ) 
		{
			contents[i]->endRepulse( ) ; 
		}
	}


}
//--------------------------------------------------------------
void testApp::update()
{
	Tweenzor::update( ofGetElapsedTimeMillis() );
	int index = 0 ; 
	vector<TileContent*>::iterator t ; 
	for ( t = contents.begin() ; t != contents.end() ; t++ ) 
	{
		//Update
		(*t)->update( ) ; 
		
		//If our input is within the bounds
		if ( (*t)->hitTest( mouseX , mouseY ) == true ) 
		{
			cout << "hitTesting over : " << index << endl ; 
			//If this index is NOT already selected index
			if ( activeTileIndex != index ) 
			{
				setNewTileActive( index ) ; 
				return ; 
			}
			else
			{
				//Still over but not triggering the initial event
				return ; 
			}
		}
		index++ ; 
	}

	//If not within over all the contents transition out active
	if ( activeTileIndex > -1 ) 
	{
		resetTiles( ) ; 
	}
}

//--------------------------------------------------------------
void testApp::draw(){

	vector<TileContent*>::iterator t ; 
	for ( t = contents.begin() ; t != contents.end() ; t++ ) 
	{
		(*t)->draw( ) ; 
	}
}

void testApp::loadTileFromXml( ) 
{
	tileXml.loadFile( "settings.xml" ) ; 

	int numTags = tileXml.getNumTags( "tile" ) ; 
	for ( int i = 0; i < numTags ; i++ ) 
	{
		
		TileContent * tile = new TileContent( ) ;
		tile->setup( ) ; 
		ofRectangle _bounds = ofRectangle( tileXml.getAttribute( "tile" , "x" , 0 , i ) , 
										   tileXml.getAttribute( "tile" , "y" , 0 , i ) , 
										   tileXml.getAttribute( "tile" , "width" , 5 , i ) , 
										   tileXml.getAttribute( "tile" , "height" , 5 , i ) ) ; 
		tile->bounds = _bounds ; 
		tile->setOrigin( ) ; 
		tile->color = ofColor::fromHex( tileXml.getAttribute( "tile" , "hexColor" , 0 , i ) ) ; 
		contents.push_back( tile ) ;
	}
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}