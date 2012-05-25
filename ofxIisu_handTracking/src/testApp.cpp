#include "testApp.h"

enum POINTER_STATUS
{
	POINTER_STATUS_NOT_DETECTED = 0,
	POINTER_STATUS_STILL = 1,
	POINTER_STATUS_OUT_OF_BOX = 2,
	POINTER_STATUS_ACTIVE = 3
};


//--------------------------------------------------------------
void testApp::setup(){

#ifndef MOUSE_DEBUG
	ofAddListener ( IisuEvents::Instance()->exitApplication , this , &testApp::exitEventHandler ) ; 

	iisuServer = CloseIisuServer() ; 
	iisuServer.setup() ; 
#endif
	
	ofBackground ( 0 , 0 , 0 ) ; 
	Tweenzor::init() ; 
	ofSetVerticalSync( true ) ; 
	ofSetFrameRate( 60 ) ; 

	hand = HandCursor() ; 
	hand.setup( ) ; 

#ifndef MOUSE_DEBUG
	hand.iisu = &iisuServer ; 
#endif

	tileManager.setup( ) ;

#ifndef MOUSE_DEBUG
	ofAddListener( IisuEvents::Instance()->HAND_CLAMP_SELECTION , this , &testApp::handClampSelectionHandler ) ; 
#endif
}

void testApp::handClampSelectionHandler ( int &args )
{
	if ( !hand.bTracked ) return ;
	cout << "HAND CLAMP HANDELED IN TEST APP!" << endl ; 
	//IF a node is active and selected ( zoom mode ) 
	if ( tileManager.selectedTile != NULL ) 
	{
		cout << "Tile IS SELECTED" ; 
		if ( tileManager.hitTest( hand.fingerCentroid.x , hand.fingerCentroid.y , tileManager.closeArea ) == true ) 
		{
			cout << " return to MENU! called " << endl ; 
			tileManager.returnToMenu( ) ;
			cout << "after returnToMenu( ) " << endl ; 
		}
		return ; 
	}
	//If on the general menu with hover states
	else
	{
		cout << "selected tile IS NULL " << endl ; 
		int activeIndex = tileManager.getIndexAtPoint( hand.fingerCentroid.x , hand.fingerCentroid.y ) ; 
		cout << "getIndexAtPoint returned : " << activeIndex << endl ; 
		if ( activeIndex > -1 ) 
		{

			//we have a match!
			tileManager.setIndexAsSelected( activeIndex ) ; 
			cout << "past setIndex as selected  " << activeIndex << endl ; 
			/*
		tileManager.setNewTileActive( activeIndex ) ; 
		if ( tileManager.activeTileIndex > -1 ) 
			tileManager.contents[tileManager.activeTileIndex]->selected( ) ; //color = ofColor( ofRandom(255) , ofRandom(255) , ofRandom(255) ) ; */
		}
	}
	
}

//--------------------------------------------------------------
void testApp::update()
{
	Tweenzor::update( ofGetElapsedTimeMillis() ) ; 
	hand.updateIisu( ) ;
	tileManager.update( ) ; 
	

#ifndef MOUSE_DEBUG
	if ( hand.bTracked == true ) 
		tileManager.input( hand.fingerCentroid.x , hand.fingerCentroid.y ) ; 
#endif
#ifdef MOUSE_DEBUG
	hand.fingerCentroid = ofVec2f( mouseX , mouseY ) ; 
	tileManager.input ( mouseX , mouseY ) ; 
#endif
	
}




//--------------------------------------------------------------
void testApp::draw(){

	ofEnableAlphaBlending( ) ; 
	tileManager.draw() ; 
	hand.draw( ) ; 
}

void testApp::exitEventHandler ( int &exitCode ) 
{
	exit() ; 
}

void testApp::exit( ) 
{
#ifndef MOUSE_DEBUG
	cout << "testApp::exit" << endl ; 
	// if we have iisu device
	if ( iisuServer.m_device )
	{
		// clear the device pointer
		iisuServer.m_device = NULL;
	}

	// if we have iisu handle
	if ( iisuServer.m_iisuHandle )
	{
		// destroy the iisu handle
		SK::Result res = Context::Instance().destroyHandle( *iisuServer.m_iisuHandle );
		if(res.failed())
		{
			cerr << "Failed to destroy handle!" << endl
				<< "Error " << res.getErrorCode() << ": " << res.getDescription().ptr() << endl;
			getchar();
		}
		// cleat the iisu handle
		iisuServer.m_iisuHandle = NULL;
	}

	// finalize context
	Context::Instance().finalize();
	ofSleepMillis( 5000 ) ; 
#endif
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	handClampSelectionHandler( x ) ; 
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}
