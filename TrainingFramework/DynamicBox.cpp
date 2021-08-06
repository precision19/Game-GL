#include "stdafx.h"
#include "DynamicBox.h"
DynamicBox::DynamicBox() {

}

DynamicBox::~DynamicBox() {

}

void DynamicBox::Init(b2World* world, Vector2 position, Vector2 dimension) {
	//make the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	body = world->CreateBody(&bodyDef);

	b2CircleShape boxShape;
	boxShape.m_radius = sqrt(dimension.x * dimension.x / 4.0f + dimension.y * dimension.y / 4.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->SetGravityScale(1000);
	fixture = body->CreateFixture(&fixtureDef);
}