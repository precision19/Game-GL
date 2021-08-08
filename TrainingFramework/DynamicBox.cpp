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
	b2CircleShape circleShape;
	circleShape.m_radius = min(dimension.x / 2.0f, dimension.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->SetGravityScale(1000);
	fixture = body->CreateFixture(&fixtureDef);
}

void DynamicBox::ApplyForce(Vector2 direction) {
	body->ApplyLinearImpulse(b2Vec2(direction.x, direction.y), body->GetWorldCenter(), 1);
}

void DynamicBox::Update(b2World* m_world) {
	ApplyForce(Vector2(body->GetMass() * m_world->GetGravity().x, body->GetMass() * m_world->GetGravity().y));
	obj->SetPosition(Vector3(body->GetPosition().x, body->GetPosition().y, obj->GetPosition().z));
	if (strncmp(obj->type, "PLAYER", 6) == 0) {
		ApplyForce(Vector2(-body->GetMass() * m_world->GetGravity().y, body->GetMass() * m_world->GetGravity().x));
	}
}

void DynamicBox::UpdatePlayer(b2World* m_world) {
	body->SetGravityScale(1);
	ApplyForce(Vector2(-2 * body->GetMass() * m_world->GetGravity().x, -2 * body->GetMass() * m_world->GetGravity().y));
}