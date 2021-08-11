#pragma once
#include "../Utilities/utilities.h"
#include "Renderer2D.h"
#include "PrefabManager.h"

class Object
{
protected:
	Vector2 m_Dimension;
	Transform transform;
	vector<Renderer*> m_Renderer;
	int ID;
	
public:
	int currentAnim;
	int i;
	char type[10];
	Object();
	void SetDimension(Vector2 dimen) { m_Dimension = dimen; }
	void SetPosition(Vector3);
	void SetScale(Vector3);
	void SetRotation(Vector3);
	void SetRenderer(int);
	void SetNativeSize(int);
	
	Vector3 GetPosition();
	Vector2 GetDimension() { return m_Dimension; }

	void Jump();
	virtual void Draw();
	virtual void Update(float);
	virtual void SetCurrentAnimation(int);

	int GetID() { return ID; };
	void SetID(int objID) { ID = objID; };

	~Object();
};

