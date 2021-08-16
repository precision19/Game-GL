#include "stdafx.h"
#include "GroundBox.h"


GroundBox::GroundBox(Object* object, Vector2 dimension, Category category)
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(object->GetPosition().x, object->GetPosition().y);
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
	b2FixtureUserData fudt;
	fudt.pointer = (uintptr_t)object;
	fixtureDef.userData = fudt;
	groundBody->CreateFixture(&fixtureDef);
	foot = new Sensor(FOOT);
	left = new Sensor(LEFT);
	if (category == CATEGORY_GROUND)
	{
		//tao foot sensor
		fixtureDef.filter.categoryBits = CATEGORY_SENSOR;
		fixtureDef.filter.categoryBits = MASK_SENSOR;
		groundBox.SetAsBox((dimension.x / 2.0f) - 0.1f, 1.0f, b2Vec2(0.0f, (dimension.y / 2.0f) - 1.0f), 0);
		fixtureDef.shape = &groundBox;
		b2FixtureUserData fudt2;
		fudt2.pointer = (uintptr_t)foot;
		fixtureDef.userData = fudt2;
		groundBody->CreateFixture(&fixtureDef);

		//tao left sensor
		fixtureDef.filter.categoryBits = CATEGORY_SENSOR;
		fixtureDef.filter.categoryBits = MASK_SENSOR;
		groundBox.SetAsBox(1.0f, (dimension.y / 2.0f) - 0.1f, b2Vec2(1.0f-(dimension.x / 2.0f), 0.0f), 0);
		fixtureDef.shape = &groundBox;
		b2FixtureUserData fudt3;
		fudt3.pointer = (uintptr_t)left;
		fixtureDef.userData = fudt3;
		groundBody->CreateFixture(&fixtureDef);

		//tao right sensor
		fixtureDef.filter.categoryBits = CATEGORY_SENSOR;
		fixtureDef.filter.categoryBits = MASK_SENSOR;
		groundBox.SetAsBox(1.0f, (dimension.y / 2.0f) - 0.1f, b2Vec2((dimension.x / 2.0f)-1.0f, 0.0f), 0);
		fixtureDef.shape = &groundBox;
		b2FixtureUserData fudt4;
		fudt4.pointer = (uintptr_t)left;
		fixtureDef.userData = fudt4;
		groundBody->CreateFixture(&fixtureDef);
	}
}

GroundBox::~GroundBox() 
{
	//delete foot;
}
