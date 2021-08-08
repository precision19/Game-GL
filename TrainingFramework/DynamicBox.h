#pragma once
#include "box2D/box2d.h"
#include "../Utilities/Math.h"
#include "Box.h"
#include <math.h>
#include "Object.h"
class DynamicBox : public Box {
private:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
	int objID;
	Object* obj;
public:
	DynamicBox();
	~DynamicBox();
	void Init(b2World* world, Vector2 position, Vector2 dimension);
	b2Body* getBody() { return body; }
	b2Fixture* getFixture() { return fixture; }
	void ApplyForce(Vector2);
	Object* getObj() { return obj; };
	void setObj(Object* object) { obj = object; }
	void Update(b2World*);
	void UpdatePlayer(b2World*);
};