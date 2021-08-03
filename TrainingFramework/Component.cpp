#include "stdafx.h"
#include "Component.h"

Component::Component()
{
	enable = true;
	transform = NULL;
}

Component::~Component()
{
}

void Component::SetTransform(Transform* objectTransform)
{
	transform = objectTransform;
}

void Component::Update(float)
{

}

void Component::CallBack(int functionId)
{
	switch (functionId)
	{
	case 0:
		CallBack0();
		break;
	case 1:
		CallBack1();
		break;
	case 2:
		CallBack2();
		break;
	default:
		printf("WARNING: call back function's ID is not correct");
		break;
	}
}

void Component::CallBack0()
{
}


void Component::CallBack1()
{
}

void Component::CallBack2()
{
}
