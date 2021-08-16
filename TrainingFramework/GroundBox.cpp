#include "stdafx.h"
#include "GroundBox.h"


GroundBox::GroundBox(Object* object, Vector2 dimension, Category category)
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(object->GetPosition().x, object->GetPosition().y);
	b2BodyUserData bdt;
	bdt.pointer = (uintptr_t)object;
	groundBodyDef.userData = bdt;
	b2Body* groundBody = Physic::GetInstance()->GetWorld()->CreateBody(&groundBodyDef);
	//make the ground fixture
	b2PolygonShape groundBox;
	groundBox.SetAsBox(dimension.x / 2.0f, dimension.y / 2.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.density = 0.0f;

	if (category == CATEGORY_GROUND)
	{
		fixtureDef.filter.categoryBits = CATEGORY_GROUND;
		fixtureDef.filter.categoryBits = MASK_GROUND;
	}
	if (category == CATEGORY_NONE)
	{
		fixtureDef.filter.categoryBits = CATEGORY_NONE;
		fixtureDef.filter.categoryBits = MASK_NONE;
	}
	if (category == CATEGORY_SENSOR)
	{
		fixtureDef.filter.categoryBits = CATEGORY_SENSOR;
		fixtureDef.filter.categoryBits = MASK_SENSOR;
		fixtureDef.isSensor = true;
	}
	groundBody->CreateFixture(&fixtureDef);
}

GroundBox::~GroundBox() 
{

}
