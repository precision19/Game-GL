#include "stdafx.h"
#include "Box.h"
#include "Physic.h"

Box::Box() 
{

}

Box::Box(Object* object, float colliderSize, Category category, bool isDynamic, string hitbox) {
	b2BodyDef bodyDef;
	if (isDynamic) bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(object->GetPosition().x, object->GetPosition().y);
	body = Physic::GetInstance()->GetWorld()->CreateBody(&bodyDef);
	b2CircleShape circleShape;
	circleShape.m_radius = colliderSize;
	b2PolygonShape groundBox;
	groundBox.SetAsBox(colliderSize / 2.0f, colliderSize / 2.0f);
	b2FixtureDef fixtureDef;
	if (hitbox == "Circle") {
		fixtureDef.shape = &circleShape;
	}
	if (hitbox == "Square") {
		fixtureDef.shape = &groundBox;
	}
	fixtureDef.density = 10.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.categoryBits = category;
	if (category == CATEGORY_PLAYER)
	{
		fixtureDef.filter.maskBits = MASK_PLAYER;
	}
	if (category == CATEGORY_NOTGRAVITY) {
		body->SetGravityScale(0);
		fixtureDef.filter.maskBits = MASK_NOTGRAVITY;
	}
	if (category == CATEGORY_SENSOR) {
		body->SetGravityScale(0);
		fixtureDef.isSensor = true;
		fixtureDef.filter.maskBits = MASK_SENSOR;
	}
	if (category == CATEGORY_SENSOR_PLAYER) {
		fixtureDef.isSensor = true;
		fixtureDef.filter.maskBits = MASK_SENSOR_PLAYER;
	}
	if (category == CATEGORY_NONE)
	{
		fixtureDef.filter.categoryBits = MASK_NONE;
	}
	b2FixtureUserData fudt;
	fudt.pointer = (uintptr_t)object;
	fixtureDef.userData = fudt;
	fixture = body->CreateFixture(&fixtureDef);
}

void Box::ApplyForce(Vector2 direction)
{
	body->ApplyLinearImpulse(b2Vec2(direction.x, direction.y), body->GetWorldCenter(), 0);
}


Vector2 Box::GetVelocity() {
	return Vector2(body->GetLinearVelocity().x, body->GetLinearVelocity().y);
}

void Box::SetVelocity(Vector2 velo) {
	body->SetLinearVelocity(b2Vec2(velo.x, velo.y));
}


Box::~Box() 
{
	body->GetWorld()->DestroyBody(body);
}

