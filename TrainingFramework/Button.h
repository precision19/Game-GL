#pragma once
#include "../Utilities/Math.h"
#include <map>
#include <vector>
#include "Input.h"
#include "Object.h"
#include "AudioManager.h"

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
	Button(string);
	virtual void SetRenderer(int);
	virtual void SetRenderer(string);
	void SetButtonID(int);
	void Update(float);
	~Button();
};