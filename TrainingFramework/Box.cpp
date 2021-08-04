#include "stdafx.h"
#include "Box.h"
Box::Box() {

}

Box::~Box() {

}

void Box::Init(b2World* world, Vector2 position, Vector2 dimension) {
	//make the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimension.x / 2.0f, dimension.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	fixture = body->CreateFixture(&fixtureDef);
}