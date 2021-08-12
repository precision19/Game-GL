#include "stdafx.h"
#include "GroundBox.h"
GroundBox::GroundBox() {

}

GroundBox::~GroundBox() {

}

void GroundBox::Init(b2World* world, Vector2 position, Vector2 dimension, Object* obj) {
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(position.x, position.y);
	b2BodyUserData bdt;
	bdt.pointer = (uintptr_t)obj;
	groundBodyDef.userData = bdt;
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	//make the ground fixture
	b2PolygonShape groundBox;
	groundBox.SetAsBox(dimension.x/2.0f, dimension.y/2.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.density = 0.0f;
	if (obj->type == GROUND) {
		fixtureDef.filter.categoryBits = CATEGORY_GROUND;
		fixtureDef.filter.categoryBits = MASK_GROUND;
	}
	if (obj->type == NONE) {
		fixtureDef.filter.categoryBits = CATEGORY_NONE;
		fixtureDef.filter.categoryBits = MASK_NONE;
	}
	groundBody->CreateFixture(&fixtureDef);
}