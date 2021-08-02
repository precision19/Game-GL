#pragma once
#include "../Utilities/Math.h"
#include <map>
#include <vector>
#include "Component.h"
#include "Input.h"

class Button : public Component
{
protected:
	Component* m_Target;
	Vector2 m_Position;
	Vector2 m_Size;
	bool m_IsPressing;
	bool m_IsSkipped;
	vector<Component*> m_Components;
	vector<int> m_CallBackFunctionIDs;
public:
	Button(Vector2, Vector2);
	void SetSize(Vector2);
	void AddListener(Component*, int);
	void Update(float);
	bool CheckClick();
	virtual void OnClick();
};