// TODO implementation

#include "gameObject.h"

Position GameObject::getPosition() const{
	return _pos;
}

Icon GameObject::getIcon() const{
	return _icon;
}

void GameObject::update(){
	//由子類別實作
}

void GameObject::moveBy(int dx,int dy){
	_pos.x() += dx;
	_pos.y() += dy;
}

void GameObject::setPosition(Position p){
	_pos = p;
}

void GameObject::setIcon(const Icon& icon){
	_icon = icon;
}
