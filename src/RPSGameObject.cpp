#include "RPSGameObject.h"
#include "iconFactory.h"
#include "unit.h"
#include "environment.h"
#include <cstdlib> // for rand()

void RPSGameObject::update(){
	_dir = static_cast<Direction>(std::rand()%4);
	switch(_dir){
		case Direction::UP:		this->moveBy(0,-1); break;
		case Direction::DOWN:	this->moveBy(0,1); break;
		case Direction::LEFT:	this->moveBy(-1,0); break;
		case Direction::RIGHT:	this->moveBy(1,0); break;
		default: break;
	}

	Position p = this->getPosition();
	if(p.x() < 0) p.x()=0;
	if(p.x() >= GAME_WINDOW_WIDTH) p.x()=GAME_WINDOW_WIDTH-1;
	if(p.y() < 0) p.y()=0;
	if(p.y() >= GAME_WINDOW_HEIGHT) p.y()=GAME_WINDOW_HEIGHT-1;
	this->setPosition(p);
}

bool RPSGameObject::intersect(ICollider* other){
	auto* otherObj = dynamic_cast<GameObject*>(other);
	if(!otherObj) return false;

	return( (this->getPosition().x() == otherObj->getPosition().x() )&&
			(this->getPosition().y() == otherObj->getPosition().y()	));
}

void RPSGameObject::onCollision(ICollider* other,int& count,bool& islose){
	auto* otherRPS = dynamic_cast<RPSGameObject*>(other);
	if (!otherRPS) return;

	RPSType otherType = otherRPS->getType();

	if(_type == otherType) return;

	if( (_type == PLAYER && otherType == APPLE) ){
		otherRPS->toBeDeleted = true;
		count++;
	}
	if( (_type == PLAYER && otherType == BOMB) ){
		islose = true;
	}
	if( (_type == BOMB && otherType == APPLE) ){
		otherRPS->setType(_type);
		otherRPS->setIcon(_icon);
	}
}

RPSType RPSGameObject::getType() const {
    return _type;
}

void RPSGameObject::setType(RPSType type) {
    _type = type;
}

void RPSGameObject::setDirection(Direction dir) {
    _dir = dir;
}
