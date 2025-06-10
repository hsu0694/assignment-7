// TODO implementation

#include "gameObjectFactory.h"
#include "iconFactory.h"
#include "RPSGameObject.h"

namespace GameObjectFactory{

GameObject* createBlock(Position pos){
	GameObject* obj = new GameObject();
	obj->setPosition(pos);
	obj->setIcon(IconFactory::blueBlock());
	return obj;
}

/*
GameObject* createPlayer(Position pos){
	GameObject* obj = new GameObject();
	obj->setPosition(pos);
	obj->setIcon(IconFactory::redPlayer());
	return obj;
}
*/

GameObject* createPlayer(Position pos){
	RPSGameObject* obj = new RPSGameObject();
	obj->setPosition(pos);
	obj->setIcon(IconFactory::Player());
	obj->setType(RPSType::PLAYER);
	return obj;
}

GameObject* createBOMBPlayer(Position pos){
	RPSGameObject* obj = new RPSGameObject();
	obj->setPosition(pos);
	obj->setIcon(IconFactory::BOMBPlayer());
	obj->setType(RPSType::BOMB);
	return obj;
}

GameObject* createAPPLEPlayer(Position pos){
	RPSGameObject* obj = new RPSGameObject();
	obj->setPosition(pos);
	obj->setIcon(IconFactory::APPLEPlayer());
	obj->setType(RPSType::APPLE);
	return obj;
}

}
