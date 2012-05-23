#include "TileManager.h"

void TileManager::setup ( ) 
{
	setupFromXml( "settings.xml" ) ;
	activeTileIndex = -2 ; 
} 

void TileManager::setupFromXml( string xmlPath ) 
{
	tileXml.loadFile( xmlPath ) ; 

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

void TileManager::input ( float x , float y ) 
{
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

void TileManager::update ( ) 
{
	vector<TileContent*>::iterator t ; 
	for ( t = contents.begin() ; t != contents.end() ; t++ ) 
	{
		(*t)->update( ) ; 
	}
}

void TileManager::draw( ) 
{
	vector<TileContent*>::iterator t ; 
	for ( t = contents.begin() ; t != contents.end() ; t++ ) 
	{
		(*t)->draw( ) ; 
	}
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