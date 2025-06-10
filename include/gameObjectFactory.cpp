// TODO 
// Finish the declaration of GameObjectFactory that
// 1. offers some methods to create a GameObject.
// 2. encapsulates the constructor from the caller. 

#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include "gameObject.h"
#include "iconFactory.h"

namespace GameObjectFactory{
	GameObject* createBlock(Position pos);  //blue block
	//GameObject* createPlayer(Position pos); //red player
	GameObject* createPlayer(Position pos);
	GameObject* createBOMBPlayer(Position pos);
	GameObject* createAPPLEPlayer(Position pos);
}

#endif
