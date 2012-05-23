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
	
	ofAddListener ( IisuEvents::Instance()->exitApplication , this , &testApp::exitEventHandler ) ; 

	iisuServer = CloseIisuServer() ; 
	iisuServer.setup() ; 

	
	ofBackground ( 0 , 0 , 0 ) ; 
	Tweenzor::init() ; 
	ofSetVerticalSync( true ) ; 
	ofSetFrameRate( 60 ) ; 

	hand = HandCursor() ; 
	hand.setup( ) ; 
	hand.iisu = &iisuServer ; 

	tileManager.setup( ) ; 

	ofAddListener( IisuEvents::Instance()->HAND_CLAMP_SELECTION , this , &testApp::handClampSelectionHandler ) ; 
}

void testApp::handClampSelectionHandler ( int &args )
{
	cout << "HAND CLAMP HANDELED IN TEST APP!" << endl ; 
	int activeIndex = tileManager.getIndexAtPoint( hand.fingerCentroid.x , hand.fingerCentroid.y ) ; 
	if ( activeIndex > -1 ) 
	{
		//we have a match!
		tileManager.setNewTileActive( activeIndex ) ; 
		tileManager.contents[tileManager.activeTileIndex]->color = ofColor( ofRandom(255) , ofRandom(255) , ofRandom(255) ) ; 
	}
}

//--------------------------------------------------------------
void testApp::update()
{
	Tweenzor::update( ofGetElapsedTimeMillis() ) ; 
	hand.updateIisu( ) ;
	tileManager.update( ) ; 
	if ( hand.bTracked == true ) 
		tileManager.input( hand.fingerCentroid.x , hand.fingerCentroid.y ) ; 
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

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}
