#ifndef RPS_H
#define RPS_H

#include "collider.h"
#include "gameObject.h"
#include "unit.h"

enum RPSType { PLAYER, BOMB, APPLE };
enum Direction { UP,DOWN,LEFT,RIGHT };

class RPSGameObject : public GameObject, public ICollider {

public:
  bool toBeDeleted = false;
  void update() override;
  void onCollision(ICollider *other,int& count,bool& islose) override;
  bool intersect(ICollider *other) override;

  RPSType getType() const;
  void setType(RPSType type);
  void setDirection(Direction);

private:
  RPSType _type;
  Direction _dir;
};
#endif
