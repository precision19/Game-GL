#include "stdafx.h"
#include "DynamicBox.h"

DynamicBox::DynamicBox(Object* object, float radius, Category category)
{
	//make the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(object->GetPosition().x, object->GetPosition().y);

	b2BodyUserData bdt;
	bdt.pointer = (uintptr_t)object;
	bodyDef.userData = bdt;

	body = Physic::GetInstance()->GetWorld()->CreateBody(&bodyDef);
	b2CircleShape circleShape;

	circleShape.m_radius = radius;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	if (category == CATEGORY_PLAYER)
	{
		fixtureDef.filter.maskBits = MASK_PLAYER;
		fixtureDef.filter.categoryBits = CATEGORY_PLAYER;
	}
	if (category == CATEGORY_NOTGRAVITY) {
		body->SetGravityScale(0);
		fixtureDef.filter.maskBits = MASK_NOTGRAVITY;
		fixtureDef.filter.categoryBits = CATEGORY_NOTGRAVITY;
	}
	fixture = body->CreateFixture(&fixtureDef);
}

DynamicBox::~DynamicBox()
{

}


void DynamicBox::ApplyForce(Vector2 direction) 
{
	body->ApplyLinearImpulse(b2Vec2(direction.x, direction.y), body->GetWorldCenter(), 0);
}


Vector2 DynamicBox::GetVelocity() {
	return Vector2(body->GetLinearVelocity().x, body->GetLinearVelocity().y);
}

void DynamicBox::SetVelocity(Vector2 velo) {
	body->SetLinearVelocity(b2Vec2(velo.x, velo.y));
}


