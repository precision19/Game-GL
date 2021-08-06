#include "stdafx.h"
#include "GroundBox.h"
GroundBox::GroundBox() {

}

GroundBox::~GroundBox() {

}

void GroundBox::Init(b2World* world, Vector2 position, Vector2 dimension) {
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(position.x, position.y);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	//make the ground fixture
	b2PolygonShape groundBox;
	groundBox.SetAsBox(dimension.x/2.0f, dimension.y/2.0f);
	printf("%f %f\n", dimension.x, dimension.y);
	groundBody->CreateFixture(&groundBox, 0.0f);
}