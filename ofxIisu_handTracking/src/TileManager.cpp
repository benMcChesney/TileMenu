#include "TileManager.h"

void TileManager::setup ( ) 
{
	setupFromXml( "settings.xml" ) ;
	activeTileIndex = -2 ;
	selectedTile = NULL ; 
	blackOutAlpha = 0.0f ; 
	globalSelectedPoint = ofVec2f( 350 , ofGetHeight()/2 - 200 ) ;

	float size = 200 ;
	float halfSize = size / 2.0f ; 
	closeArea = ofRectangle ( ofGetWidth() * .75 -halfSize , ofGetHeight() / 2 - halfSize  , size , size  ) ; 
} 

void TileManager::setupFromXml( string xmlPath ) 
{
	cout << "loading " << xmlPath << endl ; 
	bool bResult = tileXml.loadFile( xmlPath ) ; 
	cout << " result is : " << bResult << endl ; 
	int numTags = tileXml.getNumTags( "tile" ) ; 
	for ( int i = 0; i < numTags ; i++ ) 
	{
		
		TileContent * tile = new TileContent( ) ;
		tile->setup( ) ; 
		ofRectangle _bounds = ofRectangle( tileXml.getAttribute( "tile" , "x" , 0 , i ) , 
										   tileXml.getAttribute( "tile" , "y" , 0 , i ) , 
										   tileXml.getAttribute( "tile" , "width" , 5 , i ) * 2.0f , 
										   tileXml.getAttribute( "tile" , "height" , 5 , i ) * 2.0f ) ; 
		tile->bounds = _bounds ; 
		tile->setOrigin( ) ; 
		tile->color = ofColor::fromHex( tileXml.getAttribute( "tile" , "hexColor" , 0 , i ) ) ; 
		tile->loadImage( "images/food_"+ofToString(i+1)+".jpg" ) ; 
		tile->tileIndex = i ; 
		//tile->image.setAnchorPercent( 0.5 , 0.5 ) ; 
		contents.push_back( tile ) ;
	}
}

int TileManager::getIndexAtPoint ( float x , float y )
{
	for ( int i = 0 ; i < contents.size() ; i++ )
	{
		if ( contents[i]->hitTest( x , y ) == true ) 
		{
			return i ; 
		}
	}

	return -2 ; 
}

void TileManager::returnToMenu( ) 
{
	//If there is already an selectedTile
	if ( selectedTile != NULL ) 
	{
		selectedTile->unselected() ;
		int index = selectedTile->tileIndex ; 
		float returnZ = 0.0f ; 
		for ( int i = 0 ; i < contents.size() ; i++ ) 
		{
			if ( i != index ) 
			{
				Tweenzor::add( &contents[i]->z , contents[i]->z , returnZ , (float)i * 0.1f , 0.45f , EASE_OUT_QUAD ) ; 
			}
		}
		//selectedTile = NULL ; 
	}
	
	Tweenzor::add ( &blackOutAlpha , blackOutAlpha , 0.0f , 0.65f , 1.0f , EASE_OUT_QUAD ) ; 
}

void TileManager::input ( float x , float y ) 
{
	if ( selectedTile == NULL ) 
	{
		//MENU INTERACTION
		int index = 0 ; 
		vector<TileContent*>::iterator t ; 
		for ( t = contents.begin() ; t != contents.end() ; t++ ) 
		{
			//Update
			(*t)->update( ) ; 
		
			//If our input is within the bounds
			if ( (*t)->hitTest( x , y ) == true ) 
			{
				//cout << "hitTesting over : " << index << endl ; 
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

	
	
}

void TileManager::setIndexAsSelected ( int index )
{
	if ( index > -1 && index < contents.size() ) 
	{
		//not the same index !
		if ( contents[index]->bSelected == false ) 
		{
			//If there is already an selectedTile
			if ( selectedTile != NULL ) 
			{
				selectedTile->unselected() ; 
			}
			selectedTile = contents[index] ; 
			selectedTile->selected() ; 
			Tweenzor::add( &selectedTile->bounds.x , selectedTile->bounds.x , globalSelectedPoint.x , 0.65f , 0.75f , EASE_OUT_QUAD ) ; 
			Tweenzor::add( &selectedTile->bounds.y , selectedTile->bounds.y , globalSelectedPoint.y , 0.65f , 0.75f , EASE_OUT_QUAD ) ; 
			Tweenzor::add ( &blackOutAlpha , blackOutAlpha , 1.0f , 0.65f , 1.0f , EASE_OUT_QUAD ) ; 
			//Transition out other Tiles IN STYLE
			float backZ = -600 ; 
			for ( int i = 0 ; i < contents.size() ; i++ ) 
			{
				if ( i != index ) 
				{
					Tweenzor::add( &contents[i]->z , contents[i]->z , backZ , (float)i * 0.1f , 0.45f , EASE_OUT_QUAD ) ; 
				}
			}
		}
		//Selected triggered but this content is already active 
		else
		{
			//
		}
	}
	else
	{
		//invalid index
		cout << "out of range index for setIndexAsSelected!" << endl ; 
	}
}


void TileManager::update ( ) 
{
	if ( selectedTile != NULL ) 
	{
		if ( selectedTile->bSelected == false ) 
			selectedTile = NULL ; 

	}
	//vector<TileContent*>::iterator t ; 
	for ( int i = 0 ; i < contents.size() ; i++ ) 
	{
		contents[i]->update( ) ; 
	}

	
}

void TileManager::draw( ) 
{
	//vector<TileContent*>::iterator t ; 
	for ( int i = 0 ; i < contents.size() ; i++ ) 
	{
		ofPushMatrix( ) ;
			ofTranslate( 0 , 0,  contents[i]->z ) ; 
			contents[i]->draw( ) ; 
		ofPopMatrix( ) ; 
	}
	
		ofEnableAlphaBlending() ; 
		ofSetColor ( 5 , 5 , 5 , blackOutAlpha * 245.0f ) ; 
		ofSetRectMode( OF_RECTMODE_CORNER ) ;
		ofRect( 0 , 0, ofGetWidth(), ofGetHeight() ) ; 

	if ( selectedTile != NULL ) 
	{
		ofSetColor ( 255 , 255 , 255 , 255 ) ; 
		selectedTile->draw( ) ; 

		ofSetRectMode( OF_RECTMODE_CORNER ) ;
		ofSetColor ( 255 ,0 , 0 ) ; 
		ofRect ( closeArea ) ; 
	}
}

bool TileManager::hitTest( float x , float y , ofRectangle r ) 
{
	cout << "is : ( " << x << "," << y << " ) " << endl ; 
	return (( x > r.x ) && ( x < r.x + r.width ) ) && ( ( y > r.y ) && ( y < r.y + r.height )) ; 
}
		
void TileManager::input ( ofVec2f pos ) 
{
	input ( pos.x , pos.y ) ; 
}


void TileManager::setNewTileActive ( int index )
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

void TileManager::resetTiles ( ) 
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