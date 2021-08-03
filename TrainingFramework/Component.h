#pragma once
#include "Transform.h"

using namespace std;

class Component
{
public:
	Transform* transform;
	bool enable;
	Component();
	void SetTransform(Transform*);
	virtual void Update(float);
	void CallBack(int);
	virtual void CallBack0();
	virtual void CallBack1();
	virtual void CallBack2();
	virtual ~Component();
};

