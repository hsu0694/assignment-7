#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>
#include "unit.h"
#include "icon.h"
#include <iostream>
class GameObject{

	//friend class Controller;
public:

    virtual Position getPosition() const;
    virtual Icon getIcon() const;
    virtual void update();

	//I add
	virtual void moveBy(int dx,int dy);
	virtual void setPosition(Position p);
	virtual void setIcon(const Icon& icon);
	virtual ~GameObject() {}

protected:

    Position _pos;
    Icon _icon;
};

#endif
