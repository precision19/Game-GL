#pragma once
using namespace std;

class Component
{
public:
	Component();
	virtual ~Component();
	virtual void Update(float);
	void CallBack(int);
	virtual void CallBack0();
	virtual void CallBack1();
	virtual void CallBack2();
};

