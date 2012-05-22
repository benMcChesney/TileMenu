#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(15,15,15);

	selectedTile = NULL ; 
	loadTileXml( ) ;

	ofSetFrameRate( 60 ) ; 
	ofSetVerticalSync( true ) ; 

	
}

void testApp::loadTileXml( ) 
{
	tiles.clear() ; 
	xml.loadFile ( "settings.xml" ) ; 

	int numTags = xml.getNumTags( "tile" ) ; 
	for ( int i = 0 ; i < numTags ; i++ ) 
	{
		TileContainer * tile = new TileContainer( ) ; 
		ofColor tColor = ofColor::fromHex( xml.getAttribute( "tile" , "hexColor" , 0 , i ) ) ; 
		tile->setup(  xml.getAttribute( "tile" , "x" , 0 , i ) ,
					  xml.getAttribute( "tile" , "y" , 0 , i ) ,
					  xml.getAttribute( "tile" , "width" , 5 , i ) ,
				      xml.getAttribute( "tile" , "height" , 5 , i ) , tColor ) ; 
		tiles.push_back( tile ) ; 
	}
}

//--------------------------------------------------------------
void testApp::update(){

	vector<TileContainer*>::iterator tile ; 
	for ( tile = tiles.begin() ; tile != tiles.end() ; tile++ ) 
	{
		(*tile)->update( ) ; 
	}

	
	saveTileXml( ) ; 
}

void testApp::saveTileXml( ) 
{
	xml.clear() ; 

	for ( int i = 0 ; i < tiles.size() ; i++ ) 
	{
		int tagNum = xml.addTag( "tile" ) ; 
		xml.setAttribute( "tile" , "hexColor" , tiles[i]->color.getHex() , tagNum ) ; 
		xml.setAttribute( "tile" , "x" , tiles[i]->bounds.x , tagNum ) ; 
		xml.setAttribute( "tile" , "y" , tiles[i]->bounds.y , tagNum ) ; 
		xml.setAttribute( "tile" , "width" , tiles[i]->bounds.width , tagNum ) ; 
		xml.setAttribute( "tile" , "height" , tiles[i]->bounds.height , tagNum ) ; 
	}

	xml.saveFile( "settings.xml" ) ; 
}

//--------------------------------------------------------------
void testApp::draw(){

	vector<TileContainer*>::iterator tile ; 
	for ( tile = tiles.begin() ; tile != tiles.end() ; tile++ ) 
	{
		(*tile)->draw( ) ; 
	}
	
	drawGUI( ) ;
}

void testApp::drawGUI( ) 
{
	ofSetRectMode( OF_RECTMODE_CORNER ) ; 
	ofSetColor( 45 ) ; 
	int h = ofGetHeight() - 75 ; 
	ofRect( 0 , h , ofGetWidth() , 25 ) ; 

	ofSetColor( 0 ) ; 
	h = ofGetHeight() - 50 ; 
	ofRect( 0 , h , ofGetWidth() , 50 ) ; 



	ofSetColor( 215 , 215 , 215 ) ; 
	ofDrawBitmapString( ": SELECTED COLOR :" , 15 , h - 8 ) ; 
	ofDrawBitmapString( ":  X , Y , WIDTH , HEIGHT :" , 160 , h - 8 ) ; 
	ofDrawBitmapString( ": W A S D to nudge :" , 400 , h - 8 ) ; 
	ofDrawBitmapString( ": N = new square  ::  BACKSPACE = delete square :" , 560 , h - 8 ) ; 
	if ( selectedTile != NULL ) 
	{
		ofSetColor( selectedTile->color ) ;
		ofRect( 15 , h+4 , 30 , 30 ) ;
		ofSetColor( 255 , 255 , 255 ) ; 
		ofDrawBitmapString( ofToString( selectedTile->bounds.x ) + " , " + ofToString ( selectedTile->bounds.y ) + " , " +
							ofToString ( selectedTile->bounds.width ) + " , " + ofToString( selectedTile->bounds.height ) , 160 , h + 20 ) ; 
	}
	else
	{
		ofSetColor( 0 ) ; 
		ofRect( 15 , h+4 , 30 , 30 ) ;
	}

	 
}

void testApp::createRandomTile( ) 
{
	TileContainer * tile = new TileContainer( ) ; 
	tile->setup( ofRandom( 50 , ofGetWidth() - 50 ) , ofRandom( 50 , ofGetHeight() -50 ) , 50 , 50 , ofColor( ofRandom( 255 ) , ofRandom ( 255 ) , ofRandom( 255 )) ); 
	tiles.push_back( tile ) ; 
}

void testApp::deleteSelectedTile( ) 
{
	vector<TileContainer*>::iterator tile ; 
	for ( tile = tiles.begin() ; tile != tiles.end() ; tile++ ) 
	{
		if ( selectedTile == (*tile) ) 
		{
			tiles.erase( tile ) ; 
			return ; 
		}
	}

	selectedTile = NULL ;
}
//--------------------------------------------------------------
void testApp::keyPressed  (int key){

	// 119 , 97 , 115 , 100 

	//backspace 8 
	cout << key << endl ; 
	if ( selectedTile == NULL ) 
		return ; 

	//356 , 357 , 358 , 359
	switch ( key ) 
	{
		case 119 :
			selectedTile->bounds.y -= 1 ; 
			break ; 

		case 97 :
			selectedTile->bounds.x -=1 ; 
			break ; 

		case 115 :
			selectedTile->bounds.y += 1 ; 
			break ; 

		case 100 : 
			selectedTile->bounds.x += 1 ; 
			break ; 

		case 110 : 
			createRandomTile() ; 
			break ; 

		case 8 :
			deleteSelectedTile( ) ; 
			break ; 
		
		case 356 :	 
			selectedTile->bounds.width -= 1 ; 
			break ;

		case 357 : 
			selectedTile->bounds.height += 1 ;
			break ; 

		case 358 : 
			selectedTile->bounds.width += 1 ;
			break ; 

		case 359 : 
			selectedTile->bounds.height -= 1 ; 
			break ; 
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	if ( selectedTile != NULL ) 
	{
		selectedTile->bounds.x = x ; 
		selectedTile->bounds.y = y ; 
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	vector<TileContainer*>::iterator tile ; 
	bool bHitTest = false ; 
	for ( tile = tiles.begin() ; tile != tiles.end() ; tile++ ) 
	{
		bHitTest = (*tile)->hitTest( x , y ) ; 
		if ( bHitTest == true ) 
		{
			selectedTile = (*tile) ;
			return ; 
		}
	}

	//if it made it this far no match was found
	selectedTile = NULL ; 
	
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

