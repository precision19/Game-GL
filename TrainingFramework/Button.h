#pragma once
#include "../Utilities/Math.h"
#include <map>
#include <vector>
#include "Input.h"
#include "Object.h"

class Button : public Object
{
protected:
	Renderer* m_IdleRenderer;
	Renderer* m_OnPressRenerer;

	bool m_IsPressing;
	bool m_IsSkipped;

	int m_ButtonID;

	bool CheckClick();
	virtual void Idle();
	virtual void OnPressing();
	virtual void OnClicked();
public:
	Button();
	virtual void SetRenderer(int);
	void SetButtonID(int);
	void Update(float);
	~Button();
};