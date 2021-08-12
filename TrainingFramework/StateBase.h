#pragma once
#include <string>

using namespace std;

class StateBase 
{
protected:
	string m_Name;
public:
	StateBase();
	string GetName();
	virtual void OnStart();
	virtual void Draw();
	virtual void Update(float);
	virtual void OnTranslation();
	virtual ~StateBase();
};