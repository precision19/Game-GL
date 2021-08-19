#include "stdafx.h"
#include "GroundBox.h"


GroundBox::GroundBox(Object* object, Vector2 dimension, Category category)
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(object->GetPosition().x, object->GetPosition().y);
	groundBody = Physic::GetInstance()->GetWorld()->CreateBody(&groundBodyDef);
	b2FixtureDef fixtureDef;
	b2PolygonShape groundBox;
	if (category == CATEGORY_GROUND)
	{
		//make the ground fixture
		groundBox.SetAsBox(dimension.x / 2.0f, dimension.y / 2.0f);
		fixtureDef.shape = &groundBox;
		fixtureDef.density = 0.0f;
		fixtureDef.filter.categoryBits = category;
		/*fixtureDef.filter.categoryBits = MASK_GROUND;*/
	}
	else if (category == CATEGORY_NONE)
	{
		groundBox.SetAsBox(dimension.x / 2.0f, dimension.y / 2.0f);
		fixtureDef.shape = &groundBox;
		fixtureDef.density = 0.0f;
		fixtureDef.filter.categoryBits = category;
		fixtureDef.filter.categoryBits = MASK_NONE;
	}
	b2FixtureUserData fudt;
	fudt.pointer = (uintptr_t)object;
	fixtureDef.userData = fudt;
	groundBody->CreateFixture(&fixtureDef);
}

GroundBox::~GroundBox() 
{
	/*groundBody->GetWorld()->DestroyBody(groundBody);*/
}
