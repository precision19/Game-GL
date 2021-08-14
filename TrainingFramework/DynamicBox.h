#pragma once
#include <math.h>
#include "Object.h"
#include "Physic.h"

class DynamicBox : public Box {
private:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
public:
	DynamicBox(Object*, float, Category);
	~DynamicBox();
	//void Init(b2World* world, Vector2 position, Vector2 dimension, Object* obj);
	b2Body* getBody() { return body; }
	b2Fixture* getFixture() { return fixture; }
	void ApplyForce(Vector2);
	void Update(float);
	Vector2 GetVelocity();
	void SetVelocity(Vector2);
};